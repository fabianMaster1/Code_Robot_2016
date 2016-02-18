/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: srategie.c
 * Auteur  	: Quentin
 * Revision	: 1.0
 * Date		: 07 f�vrier 2015, 22:47
 *******************************************************************************
 *
 *
 ******************************************************************************/

/******************************************************************************/
/******************************** INCLUDES ************************************/
/******************************************************************************/

#include "system.h"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


void strategie()
{
    COULEUR = couleur_depart();
    /*
     * Definit la configuration des coquillages CONFIG_1 - CONFIG_5
    */
    CONFIG_COQUILLAGE = CONFIG_4;
    
    #ifdef GROS_ROBOT
        // Inits avant d�marage du robot :
        init_jack();

        //if (COULEUR == VIOLET)
            //synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
        //else
            //synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);
        //delay_ms(1000);
        while(!SYS_JACK);

        // D�marage du match
        TIMER_90s = ACTIVE;
        EVITEMENT_ADV_AVANT = OFF;
        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;

        init_position_robot(78., 1235., 0.);
                
        /*
        //Init de d�part
        angle_AX12(PINCE_D, 285, 300, AVEC_ATTENTE); //Position rang�
        angle_AX12(PINCE_G, 735, 300, AVEC_ATTENTE); //Position rang�
        angle_AX12(ASCENSEUR, 235, 512, AVEC_ATTENTE);   //Position basse
        angle_AX12(ROT_FILET, 85, 300, AVEC_ATTENTE);    //Position relev� (Tout d�but)
        angle_AX12(OUVERTURE_FILET, 256, 300, AVEC_ATTENTE);    //Position ferm�
        angle_AX12(AX_CALAGE_CONE, 750, 1023, AVEC_ATTENTE);
        //angle_AX12(AX_US_GAUCHE, 100, 200, AVEC_ATTENTE);    //Position regarde cot� droit
        //angle_AX12(AX_US_DROIT, 625, 1023, AVEC_ATTENTE);    //Position regarde cot� gauche
        lancer_autom_AX12();
        angle_AX12(DEPLOIMENT_BRAS_FILET, 820, 200, SANS_ATTENTE);   //Position remont�
        delay_ms(100);
        
      
        
    passe_part(500, 1235, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
    passe_part(1100, 250, MARCHE_AVANT, 60, MILIEU_TRAJECTOIRE);
    passe_part(1000, 200,MARCHE_AVANT, 70, MILIEU_TRAJECTOIRE);
    FLAG_ACTION = POISSONS;
    passe_part(900, 175,MARCHE_AVANT, 80, MILIEU_TRAJECTOIRE);
    passe_part(800, 157,MARCHE_AVANT, 80, MILIEU_TRAJECTOIRE);
    passe_part(450, 157,MARCHE_AVANT, 80, FIN_TRAJECTOIRE);

    angle_AX12(DEPLOIMENT_BRAS_FILET, 530, 300, SANS_ATTENTE);   //Position d�ploy�
    while(read_data(DEPLOIMENT_BRAS_FILET, LIRE_POSITION_ACTU) > 520);
    angle_AX12(OUVERTURE_FILET, 860, 400, SANS_ATTENTE);    //Position ouverte
    while(read_data(OUVERTURE_FILET, LIRE_POSITION_ACTU) < 850);
    angle_AX12(ROT_FILET, 375, 200, SANS_ATTENTE);   //Position Interm�diaire (avant de rentrer dans l'eau)
    while(read_data(ROT_FILET, LIRE_POSITION_ACTU) < 370);
    delay_ms(150);

    rejoindre(637, 157, MARCHE_ARRIERE, 60);

    angle_AX12(ROT_FILET, 690, 150, SANS_ATTENTE);   //Position dans l'eau
    while(read_data(ROT_FILET, LIRE_POSITION_ACTU) < 685);

    rejoindre(795, 150, MARCHE_ARRIERE, 50);

    angle_AX12(ROT_FILET, 1005, 600, SANS_ATTENTE);  //Position Fin (poissons r�cup�r�s)
    while(read_data(ROT_FILET, LIRE_POSITION_ACTU) < 1000)
    {
        delay_ms(1000);
        static short Compteur_Bloquage_Filet = 0;
        if(read_data(ROT_FILET, LIRE_POSITION_ACTU) <= 1000 && read_data(ROT_FILET, LIRE_POSITION_ACTU) >= 690)
        {//Tjr pas atteind le seuil alors reculer un peu
            rejoindre(740, 150, MARCHE_AVANT, 35);
            while(get_X() > 755);
            Compteur_Bloquage_Filet = 1;
            delay_ms(100);
        }
        if(read_data(ROT_FILET, LIRE_POSITION_ACTU) <= 1000 && read_data(ROT_FILET, LIRE_POSITION_ACTU) >= 690 && Compteur_Bloquage_Filet == 1)
        {//Augmente la patate!
            angle_AX12(ROT_FILET, 1005, 800, SANS_ATTENTE);  //Position Fin (poissons r�cup�r�s)
            delay_ms(200);
            Compteur_Bloquage_Filet = 2;
            //delay_ms(200);
            //angle_AX12(ROT_FILET, 1005, 900, SANS_ATTENTE);  //Position Fin (poissons r�cup�r�s)
        }
        if(read_data(ROT_FILET, LIRE_POSITION_ACTU) < 1000 && read_data(ROT_FILET, LIRE_POSITION_ACTU) >= 690 && Compteur_Bloquage_Filet == 2)   
        {//Tjr pas atteind le seuil alors faire des accout
            //angle_AX12(ROT_FILET, 790, 800, SANS_ATTENTE);  //Position Fin (poissons r�cup�r�s)
            unsigned short temp = 0;
            while(temp < 3)
            {//R�p�te le mouvement 3 fois
            angle_AX12(DEPLOIMENT_BRAS_FILET, 590, 400, SANS_ATTENTE);   //Position d�ploy�
            delay_ms(50);
            angle_AX12(DEPLOIMENT_BRAS_FILET, 460, 400, SANS_ATTENTE);   //Position d�ploy�
            delay_ms(50);
            temp++;
            }
        }
    }
    angle_AX12(DEPLOIMENT_BRAS_FILET, 600, 350, SANS_ATTENTE);   //Position interm�diaire (pour pass� la barre du filet)
    while(read_data(DEPLOIMENT_BRAS_FILET, LIRE_POSITION_ACTU) < 590);
    
    passe_part(1100, 250, MARCHE_ARRIERE, 50, DEBUT_TRAJECTOIRE);
    passe_part(1150, 210,MARCHE_ARRIERE, 80, MILIEU_TRAJECTOIRE);
    passe_part(1250, 155,MARCHE_ARRIERE, 80, MILIEU_TRAJECTOIRE);
    passe_part(1300, 158,MARCHE_ARRIERE, 80, FIN_TRAJECTOIRE);

    angle_AX12(DEPLOIMENT_BRAS_FILET, 530, 150, AVEC_ATTENTE);   //Position d�ploy�
    angle_AX12(ROT_FILET, 375, 300, AVEC_ATTENTE);   //Position Interm�diaire (avant de rentrer dans l'eau)
    lancer_autom_AX12();
    delay_ms(1000);
    */
    #endif
  
    #ifdef PETIT_ROBOT
            passe_part(500, 1050, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
            passe_part(750,1000,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
            passe_part(1200, 1000, MARCHE_AVANT, 70, FIN_TRAJECTOIRE);
            rejoindre(1050, 1000, MARCHE_ARRIERE, 100);
    #endif
}



void homologation()
{
    COULEUR = couleur_depart();

    #ifdef GROS_ROBOT

      // Inits avant d�marage du robot :
        init_jack();
        /*
        if (COULEUR == VIOLET)
            synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
        else
            synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);
        */
        while(!SYS_JACK);

        // D�marage du match
        TIMER_90s = ACTIVE;
        EVITEMENT_ADV_AVANT = ON;
        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;

        init_position_robot(180., 988., 0.);

        delay_ms(1000);

    #endif

    #ifdef PETIT_ROBOT
    #endif
}

void reglage_odometrie()
{
    delay_ms(2000);
    //while(!SYS_JACK);
    COULEUR = couleur_depart();
    
    #ifdef GROS_ROBOT
        init_jack();
    #endif
    
    EVITEMENT_ADV_ARRIERE = OFF;
    EVITEMENT_ADV_AVANT = OFF;

    init_position_robot (0, 0, 0);
    init_position_robot (-100, 0, 0);
    rejoindre(0, 0, MARCHE_AVANT, 100);
    trapeze(MARCHE_AVANT);
    trapeze(MARCHE_AVANT);
    trapeze(MARCHE_AVANT);
    trapeze(MARCHE_AVANT);
    trapeze(MARCHE_AVANT);

//           faire_des_tours(-32);
            while(1);
////
////            TIMER_DEBUG = ACTIVE;
//            init_position_robot(0, 0, 0);
            ////Horraire
//       rejoindre(2000, 0, MARCHE_AVANT, 50);
//       orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter(-90, 50);
//        rejoindre(2000, 0, MARCHE_AVANT, 50);
//        orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter (-90, 50);
//        rejoindre(2000, 0, MARCHE_AVANT, 50);
//        orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter (-90, 50);
//        rejoindre(2000, 0, MARCHE_AVANT, 50);
//        orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter (-90, 50);
//        rejoindre(2000, 0, MARCHE_AVANT, 50);
//        orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter (-90, 50);
//        rejoindre(2000, 0, MARCHE_AVANT, 50);
//        orienter(90, 50);
//        rejoindre(300, 0, MARCHE_AVANT, 50);
//        orienter(-90, 50);


            //// Anti horaire
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter(90, 50);
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter (90, 50);
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter (90, 50);
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter (90, 50);
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter (90, 50);
        rejoindre(2000, 0, MARCHE_AVANT, 50);
        orienter(-90, 50);
        rejoindre(300, 0, MARCHE_AVANT, 50);
        orienter(90, 50);
        rejoindre(500, 0, MARCHE_AVANT, 100);


//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(2000, 0, MARCHE_AVANT, 100);
//        rejoindre(300, 0, MARCHE_AVANT, 100);
//        rejoindre(500, 0, MARCHE_AVANT, 100);
//        TIMER_DEBUG = DESACTIVE;

        delay_ms(10000);
}