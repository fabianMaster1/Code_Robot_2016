/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: main.c
 * Auteur  	: Quentin
 * Revision	: 1.0
 * Date		: 22 octobre 2015, 23:55
 *******************************************************************************
 *
 *
 ******************************************************************************/

#include "system.h"
#include <xc.h>

/******************************************************************************/
/************************ Configurations Bits *********************************/
/******************************************************************************/

// DSPIC33FJ128MC804 Configuration Bit Settings

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = OFF //ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSECMD  //CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)



/******************************************************************************/
/********************* DECLARATION DES VARIABLES GLOBALES *********************/
/******************************************************************************/

    uint8_t COULEUR;

    uint8_t DETECTION;
    uint8_t EVITEMENT_ADV_AVANT;
    uint8_t EVITEMENT_ADV_ARRIERE;
    uint8_t STRATEGIE_EVITEMENT;
    uint16_t FLAG_ACTION;
    uint8_t FLAG_EVITEMENT_STRATEGIQUE;
    uint8_t ETAT_AUTOM;
    uint16_t COMPTEUR_MARCHE;
    uint8_t COMPTEUR_TEMPS_MATCH;
    uint8_t CONFIG_COQUILLAGE;


    int obstacle[30][20];
	int calcul_en_cours=OFF;
    int curseur;
    int curseur_obstacle;
    int itineraire[nb_point_max][3];
    int itineraire_basique[nb_point_max][3];
    int itineraire_court[nb_point_max][3];
    int point_obstacle[nb_point_max][3];
    int x_actuel;
    int y_actuel;
    int x_obj;
    int y_obj;
    int id_evitement = 0;
    int id_evitement_initial = 0;
    int chemin_court=0;
    uint16_t compteur_evitement=0;
    int precedent_obstacle[7];
    uint8_t pousser_tour;
    uint8_t coquillage_phase_1;
    uint8_t coquillage_phase_2;
    uint8_t fin_strategie_cause_evitement = 0;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

    
int main(int argc, char** argv)
{
    init_system();
    init_evitement();
    TIMER_DEBUG = DESACTIVE;
    delay_ms(500);

    
    init_decalage_AX12();
    init_position_AX12();

    
    //Init Suppl�mentaire
#ifdef GROS_ROBOT
    synchro_AX12(AX_US, 0, 1023, SANS_ATTENTE);
#endif
    
    while(SYS_JACK);

    strategie();

    //reglage_odometrie();
    
    while(1);
    return (EXIT_SUCCESS);
}



/*
 angle_AX12(PORTE_D, 350, 1023, SANS_ATTENTE);  //Position Ferm�
 * angle_AX12(PORTE_G, 655, 1023, SANS_ATTENTE);//Position Ferm�
 
 
 
 */