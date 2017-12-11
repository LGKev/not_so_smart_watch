/*
 * tmp006.c
 *
 *  Created on: Dec 10, 2017
 *      Author:
 */
#include "tmp006.h"
#include "msp.h"
#include "math.h"

extern int Vobj ;
extern int Tdie ;
extern  long double S0;
extern float temp;
extern volatile float Temperature_C;
extern volatile float Temperature_F ;
extern volatile float Temperature_K;
volatile float temp_array[5];
volatile uint8_t temp_num=0;

void GPIO_configure_TMP006(){
    /* Select I2C function for I2C_SCL(P6.5) & I2C_SDA(P6.4) */
    P6->SEL0 |= BIT5 | BIT4;
    P6->SEL1 &= ~(BIT5 | BIT4 );
}

void I2C_configure_tmp006(){
    // Initialize USCI_B1 and I2C Master to communicate with slave devices
    //Reset all registers/disable, master, I2C mode, SMCLK
    EUSCI_B1->CTLW0 = (EUSCI_B_CTLW0_SWRST | EUSCI_B_CTLW0_MST
            | EUSCI_B_CTLW0_MODE_3 | EUSCI_B_CTLW0_SSEL__SMCLK); // Sync mode @@CHECKTHIS@@
    //no autostop to manually control when stop bit is sent
    EUSCI_B1->CTLW1 = EUSCI_B_CTLW1_ASTP_0;
    //set clock divider for SMCLK at 3MHz for 400KBPS data rate
    EUSCI_B1->BRW = (uint16_t) (3000000 / 40000);

    /* Enable I2C Module to start operations */
    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;
}

void I2C_write16(unsigned char pointer, uint16_t writeByte){
    //Disable TX IE
    EUSCI_B1->IE &= ~EUSCI_B_IE_TXIE0;
    // Set master to transmit mode PL
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;
    // Clear any existing interrupt flag PL
    EUSCI_B1->IFG &= ~EUSCI_B_IFG_TXIFG0;
    // Wait until ready to write PL
    while (EUSCI_B1->STATW & EUSCI_B_STATW_BBUSY)
        ;
    // Initiate start and send first character
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
    //Wait for TX Buf to be empty
    //while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0));
    EUSCI_B1->TXBUF = pointer;

    // Send the MSB to SENSOR
    //Wait for TX Buf to be empty and send data
    //while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0));
    EUSCI_B1->TXBUF = (unsigned char) (writeByte >> 8);
    //while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0));
    EUSCI_B1->TXBUF = (unsigned char) (writeByte & 0xFF);

    //Wait for TX Buf to be empty then send stop command
    //while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0));
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
}

int I2C_read16(unsigned char writeByte){
    volatile int val = 0;
    volatile int valScratch = 0;

    //Disable TX IE
    EUSCI_B1->IE &= ~EUSCI_B_IE_TXIE0;
    // Set master to transmit mode PL
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;
    // Clear any existing interrupt flag PL
    EUSCI_B1->IFG &= ~EUSCI_B_IFG_TXIFG0;
    // Wait until ready to write PL
    while (EUSCI_B1->STATW & EUSCI_B_STATW_BBUSY)
        ;
    // Initiate start and send first character
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
    //Wait for TX Buf to be empty
    while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0))
        ;
    EUSCI_B1->TXBUF = writeByte;
    //Wait for TX Buf to be empty and send stop data
    while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0))
        ;
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
    while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0))
        ;

    //Set to recieve mode and send start condition
    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_TR;
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
    //wait for the RX Buf to fill
    while (!(EUSCI_B1->IFG & EUSCI_B_IE_RXIE0))
        ;
    //read first 16 bits
    val = (EUSCI_B1->RXBUF & EUSCI_B_RXBUF_RXBUF_MASK);
    //send stop command and wait for TXBUF and RXBuf to finish
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
    while (!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0))
        ;
    while (!(EUSCI_B1->IFG & EUSCI_B_IE_RXIE0))
        ;
    //Read rest of RXBUF
    valScratch = (EUSCI_B1->RXBUF & EUSCI_B_RXBUF_RXBUF_MASK);
    // Shift val to top MSB
    val = (val << 8);
    // Read from I2C RX Register and write to LSB of val
    val |= valScratch;
    // Return temperature value
    return (int16_t) val;
}

void TMP006_init(void)
{
    /* Specify slave address for TMP006 */
    EUSCI_B1->I2CSA = TMP006_SLAVE_ADDRESS;

    /* Reset TMP006 */
    I2C_write16(TMP006_WRITE_REG, TMP006_RST);

    volatile int i;
    for (i = 10000; i > 0; i--)  ;

    /* Power-up and re-enable device for sampling once a second */
    I2C_write16(TMP006_WRITE_REG, TMP006_POWER_UP | TMP006_CR_1);
}

int TMP006_readDeviceId(){
    /* Specify slave address for TMP006 */
    I2C_setslave(TMP006_SLAVE_ADDRESS);

    return I2C_read16(TMP006_P_DEVICE_ID);
}

void I2C_setslave(unsigned int slaveAdr)
{
    /* Specify slave address for I2C */
    EUSCI_B1->I2CSA = slaveAdr;

    /* Enable and clear the interrupt flag */
    EUSCI_B1->IFG &= ~(EUSCI_B_IFG_TXIFG0 + EUSCI_B_IFG_RXIFG0);
}

int TMP006_readObjectVoltage(void)
{
    /* Specify slave address for TMP006 */
    I2C_setslave(TMP006_SLAVE_ADDRESS);

    return I2C_read16(TMP006_P_VOBJ);
}

int TMP006_readAmbientTemperature(){
    /* Specify slave address for TMP006 */
    I2C_setslave(TMP006_SLAVE_ADDRESS);

    return I2C_read16(TMP006_P_TABT);
}

long double TMP006_getTemp(){
    volatile int Vobj = 0;
    volatile int Tdie = 0;

    Vobj = TMP006_readDeviceId();

    /* Read the object voltage */
    Vobj = TMP006_readObjectVoltage();

    /* Read the ambient temperature */
    Tdie = TMP006_readAmbientTemperature();
    Tdie = Tdie >> 2;

    /* Calculate TMP006. This needs to be reviewed and calibrated */
    long double Vobj2 = (double) Vobj * .00000015625;
    long double Tdie2 = (double) Tdie * .03525 + 273.15;

    /* Initialize constants */
    S0 = 6 * pow(10, -14);
    long double a1 = 1.75 * pow(10, -3);
    long double a2 = -1.678 * pow(10, -5);
    long double b0 = -2.94 * pow(10, -5);
    long double b1 = -5.7 * pow(10, -7);
    long double b2 = 4.63 * pow(10, -9);
    long double c2 = 13.4;
    long double Tref = 298.15;

    /* Calculate values */
    long double S = S0
            * (1 + a1 * (Tdie2 - Tref) + a2 * pow((Tdie2 - Tref), 2));
    long double Vos = b0 + b1 * (Tdie2 - Tref) + b2 * pow((Tdie2 - Tref), 2);
    volatile long double fObj = (Vobj2 - Vos) + c2 * pow((Vobj2 - Vos), 2);
    volatile long double Tobj = pow(pow(Tdie2, 4) + (fObj / S), .25);
    Tobj = (9.0 / 5.0) * (Tobj - 273.15) + (32-13);

    /* Return temperature of object */
    return (Tobj);
}

void temp_array_fxn(float temp){
    temp_array[temp_num]=temp;
    temp_num++;
    float average=0;
    if(temp_num==5){
        temp_num=0;
        uint8_t i;
        for(i=0; i<5; i++){
        average+=temp_array[i];
        }
        Temperature_F=average/5;
        Temperature_C=(Temperature_F-32)*(float)(5.0/9.0);
        Temperature_K=Temperature_C+273.15;
    }
}

