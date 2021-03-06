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
    
    #ifdef GROS_ROBOT


        // Inits avant d�marage du robot :
        init_jack();

        if (COULEUR == JAUNE)
            synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
        else
            synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);

        while(!SYS_JACK);

        // D�marage du match
        TIMER_90s = ACTIVE;
        EVITEMENT_ADV_AVANT = ON;
        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;

        init_position_robot(180., 988., 0.);
        FLAG_ACTION = INIT_ASCENSEUR;

        delay_ms(1000);

        // Direction Gobelet face zone d�part
        passe_part(620, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
        passe_part(683, 991, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(675, 998, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(742, 1112,MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        // Direction Gobelet pour lib�rer les deux pieds pour R2
        passe_part(700, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
        if (COULEUR == JAUNE)
            passe_part(650, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        else
             passe_part(630, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(320, 400, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);


        // Retour au bercail pour d�pose N�1
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
        passe_part(570,455,MARCHE_ARRIERE,100,DEBUT_TRAJECTOIRE);

        FLAG_ACTION = NE_RIEN_FAIRE;
        EVITEMENT_ADV_ARRIERE = OFF;
        EVITEMENT_ADV_AVANT = ON;
        passe_part(550,550,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
        passe_part(650,800,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);

        // On d�sactive dans la zone de d�part
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(558,990,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
        passe_part(270,990,MARCHE_AVANT,100,FIN_TRAJECTOIRE);

        // On v�rifie confirme que le gobelet a bien �t� attrap�
        uint8_t etat_pince_G = LIBRE, etat_pince_D = LIBRE;

        // on enregistrer l'�tat des pinces (remplies ou non)
        if (check_capteur(DROITE) == 0)
            etat_pince_D = FERMER;
        if (check_capteur(GAUCHE) == 0)
            etat_pince_G = FERMER;

        // on d�pose d'abord au centre de la zone si dispo
        if (etat_pince_G == FERMER)
        {
            pince(GAUCHE, OUVERTE);
        }
        // sinon on d�pose l'autre pince
        if (etat_pince_D == FERMER)
        {
            pince(DROITE, OUVERTE);
        }

        delay_ms(2000);

         // On sors de la zone de d�part
        delay_ms(500);
        avancer_reculer(-100, 50);

        // Pas de gobelet dans les pinces : (si 0 gobelets attrap�s ascensuer d�j� rang� ...)
        pince(GAUCHE, RANGEMENT);
        pince(DROITE, RANGEMENT);
        delay_ms(500);
        ascenseur(ARRIERE);

        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;

        // On va vers les marches
        FLAG_EVITEMENT_STRATEGIQUE = MONTEE_EVITEMENT_EN_COURS;
        passe_part(750, 1000, MARCHE_ARRIERE, 50, DEBUT_TRAJECTOIRE);
        passe_part(1220, 830, MARCHE_AVANT, 60, DEBUT_TRAJECTOIRE);
        passe_part(1220, 1240, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
        orienter(90, 100);

        marche();




//        // ancien strat
//        // Inits avant d�marage du robot :
//        init_jack();
//
//        if (COULEUR == JAUNE)
//            synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
//        else
//            synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);
//
//        while(!SYS_JACK);
//
//        // D�marage du match
//        TIMER_90s = ACTIVE;
//        EVITEMENT_ADV_AVANT = ON;
//        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;
//
//        init_position_robot(180., 988., 0.);
//        FLAG_ACTION = INIT_ASCENSEUR;
//
//        delay_ms(1000);
//
//        // Direction Gobelet face zone d�part
//        passe_part(620, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
//        passe_part(683, 991, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(675, 998, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(742, 1112,MARCHE_AVANT, 100, FIN_TRAJECTOIRE);
//
//        // Direction Gobelet pour lib�rer les deux pieds pour R2
//        passe_part(700, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
//        if (COULEUR == JAUNE)
//            passe_part(650, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        else
//             passe_part(630, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(320, 400, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
//
//
//        // Retour au bercail pour d�pose N�1
//        EVITEMENT_ADV_AVANT = OFF;
//        EVITEMENT_ADV_ARRIERE = ON;
//        passe_part(570,455,MARCHE_ARRIERE,100,DEBUT_TRAJECTOIRE);
//
//        FLAG_ACTION = NE_RIEN_FAIRE;
//        EVITEMENT_ADV_ARRIERE = OFF;
//        EVITEMENT_ADV_AVANT = ON;
//        passe_part(550,550,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//        passe_part(650,800,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//
//        // On d�sactive dans la zone de d�part
//        EVITEMENT_ADV_AVANT = OFF;
//        passe_part(558,990,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//        passe_part(270,990,MARCHE_AVANT,100,FIN_TRAJECTOIRE);
//
//        // On v�rifie confirme que le gobelet a bien �t� attrap�
//        uint8_t etat_pince_G = LIBRE, etat_pince_D = LIBRE, temp1 = 1, temp2 = 1;
//
//        // on enregistrer l'�tat des pinces (remplies ou non)
//        if (check_capteur(DROITE) == 0)
//            etat_pince_D = FERMER;
//        if (check_capteur(GAUCHE) == 0)
//            etat_pince_G = FERMER;
//
//        // on d�pose d'abord au centre de la zone si dispo
//        if (etat_pince_G == FERMER)
//        {
//            pince(GAUCHE, OUVERTE);
//            etat_pince_G = LIBRE;
//        }
//        // sinon on d�pose l'autre pince
//        else if (etat_pince_D == FERMER)
//        {
//            pince(DROITE, OUVERTE);
//            etat_pince_D = LIBRE;
//        }
//        // enfin si rien du tout on range l'ascenseur
//        else
//        {
//            pince(DROITE, RANGEMENT);
//            pince(GAUCHE, RANGEMENT);
//            ascenseur(ARRIERE);
//        }
//
//        delay_ms(2000);
//
//        // On a encore un gobelet � d�poser
//        if (etat_pince_D == FERMER) //strat normale (2 gobelets du d�part)
//        {
//            delay_ms(500);
//            avancer_reculer(-100, 50);
//
//            EVITEMENT_ADV_ARRIERE = ON;
//
//            passe_part(750, 1000, MARCHE_ARRIERE, 50, DEBUT_TRAJECTOIRE);
//            pince(GAUCHE, RANGEMENT);
//
//            EVITEMENT_ADV_ARRIERE = OFF;
//            EVITEMENT_ADV_AVANT = ON;
//
//            // on traverse le terrain
//            plus_court(1900, 900, MARCHE_AVANT, 60, MILIEU_TRAJECTOIRE, 0);
////            passe_part(1100, 900, MARCHE_AVANT, 70, MILIEU_TRAJECTOIRE);
////            passe_part(1900, 900, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//            passe_part(2300, 545, MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
//            passe_part(2760, 545, MARCHE_AVANT, 50, FIN_TRAJECTOIRE);
//            // D�pose du gobelet
//            pince(DROITE, OUVERTE);
//
//            // On essaye d'avoir celui de l'adversaire
//            avancer_reculer(-80, 50);
//            FLAG_ACTION = ATTRAPE_GOBELET;
//
//            // On s'�loigne du gobelet
//            EVITEMENT_ADV_AVANT = OFF;
//            EVITEMENT_ADV_ARRIERE = ON;
//            rejoindre (2670, get_Y(), MARCHE_ARRIERE, 60);
//
////            // Recalage contre la bordure
////            orienter(-90, 100);
////            //ne pas mettre d'�vitement adv : risque de voir un robot dans la zone adverse
////            EVITEMENT_ADV_ARRIERE = OFF;
////            avancer_reculer(-200, 50);
////            init_Y(667);
////            init_orientation(-90);
//
//
//            // On se dirige vers le clap en essayant d'attraper le gobelet adverse au passage
//            EVITEMENT_ADV_ARRIERE = OFF;
//            EVITEMENT_ADV_AVANT = ON;
//            rejoindre(2670, 225, MARCHE_AVANT, 60);
//            rejoindre(2550, 210, MARCHE_AVANT, 60);
//
//            FLAG_ACTION = NE_RIEN_FAIRE;
//
//            // On fait le clap
//            bras(GAUCHE, OUVERT);
//            rejoindre (2220, 195, MARCHE_AVANT, 50);
//
//            if (check_capteur(GAUCHE) == 0) // 2 gobelets du d�part + gobelet adverse
//            {
//                //depose du gobelet dans la zone de gauche
//                //+ Alignement marches
//                bras(GAUCHE, FERMER);
//                passe_part (2100, 800, MARCHE_AVANT, 80, DEBUT_TRAJECTOIRE);
//                passe_part (2200, 1210, MARCHE_AVANT, 80, MILIEU_TRAJECTOIRE);
//                passe_part (2300, 1300, MARCHE_AVANT, 80, MILIEU_TRAJECTOIRE);
//                passe_part (2400, 1450, MARCHE_AVANT, 80, MILIEU_TRAJECTOIRE);
//                passe_part (2700, 1450, MARCHE_AVANT, 80, FIN_TRAJECTOIRE);
//                pince(GAUCHE, OUVERTE);
//
//                delay_ms(500);
//
//                // recalage contre les amrches
//                EVITEMENT_ADV_AVANT = OFF;
//                EVITEMENT_ADV_ARRIERE = ON;
//                rejoindre (2200, 1450, MARCHE_ARRIERE, 100);
//                pince(DROITE, RANGEMENT);
//                pince(GAUCHE, RANGEMENT);
//                delay_ms(500);
//                ascenseur(ARRIERE);
//
//                //desactiver evitement
//                EVITEMENT_ADV_ARRIERE = OFF;
//                FLAG_EVITEMENT_STRATEGIQUE = EN_ROUTE_MONTEE_MARCHE;
//                avancer_reculer(-200, 100);
//                init_X(2143);
//                init_orientation(0);
//
//                EVITEMENT_ADV_AVANT = ON;
//                rejoindre (2300, 1450, MARCHE_AVANT, 100);
//
//                //alignement marche
//                passe_part(2220, 1220, MARCHE_AVANT, 70, DEBUT_TRAJECTOIRE);
//                passe_part(1930, 830, MARCHE_AVANT, 70, MILIEU_TRAJECTOIRE);
//                passe_part(1240, 830, MARCHE_AVANT, 70, MILIEU_TRAJECTOIRE);
//                passe_part(1240, 1260, MARCHE_AVANT, 70, FIN_TRAJECTOIRE);
//                orienter(90, 100);
//
//            }
//            // Strate normale 2 gobelet d�part mais pas gobelet adverse
//            // /!\ CAS LE PLUS PROBABLE /!\
//
//            else // Pas de gobelet => direction les marches
//            {
//                bras(GAUCHE, FERMER);
//                pince(DROITE, RANGEMENT);
//                pince(GAUCHE, RANGEMENT);
//                delay_ms(500);
//                ascenseur(ARRIERE);
//
//                //se diriger vers les marches
//                EVITEMENT_ADV_AVANT = ON;
//                FLAG_EVITEMENT_STRATEGIQUE = EN_ROUTE_MONTEE_MARCHE;
//                passe_part(1200, 830, MARCHE_AVANT, 60, DEBUT_TRAJECTOIRE);
//                passe_part(1200, 1240, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
//                orienter(90, 100);
//            }
//
//
//            //rejoindre(2600, 400, MARCHE_AVANT, 100);
//        }
//        else // 1 ou 0 gobelets au d�part (soit plus de gobelet dans les pinces)
//        {
//            // On sors de la zone de d�part
//            delay_ms(500);
//            avancer_reculer(-100, 50);
//
//            // Pas de gobelet dans les pinces : (si 0 gobelets attrap�s ascensuer d�j� rang� ...)
//            pince(GAUCHE, RANGEMENT);
//            pince(DROITE, RANGEMENT);
//            delay_ms(500);
//            ascenseur(ARRIERE);
//
//            EVITEMENT_ADV_AVANT = OFF;
//            EVITEMENT_ADV_ARRIERE = ON;
//            passe_part(750, 1000, MARCHE_ARRIERE, 50, DEBUT_TRAJECTOIRE);
//
//            EVITEMENT_ADV_ARRIERE = OFF;
//            EVITEMENT_ADV_AVANT = ON;
//
//            // On se dirige dans la zone de droite en traversant le terrain
//            //passe_part(1100, 900, MARCHE_AVANT, 70, MILIEU_TRAJECTOIRE);
//            //passe_part(1900, 900, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//            plus_court(1900, 900, MARCHE_AVANT, 60, MILIEU_TRAJECTOIRE, 0);
//            passe_part(2300, 545, MARCHE_AVANT, 60, MILIEU_TRAJECTOIRE);
//            ascenseur(AVANT);
//            passe_part(2670, 545, MARCHE_AVANT, 50, FIN_TRAJECTOIRE);
//
//            // on va faire le clap en tentant le gobelet adverse au passage
//            pince(GAUCHE, OUVERTE);
//            delay_ms(500);
//            FLAG_ACTION = ATTRAPE_GOBELET;
//            rejoindre(2670, 240, MARCHE_AVANT, 50);
//
//            cibler (2550, 210, 40);
//            rejoindre(2550, 210, MARCHE_AVANT, 50);
//
//            FLAG_ACTION = NE_RIEN_FAIRE;
//
//            // On fait le clap
//            bras(GAUCHE, OUVERT);
//            rejoindre (2210, 195, MARCHE_AVANT, 50);
//
//
//
//            if (check_capteur(GAUCHE) == 0) // 1 ou 0 gobelet au d�part + gobelet adverse
//            {
//                // Si on a eu le gobelet adverse
//                bras(GAUCHE, FERMER);
//                EVITEMENT_ADV_AVANT = OFF;
//                EVITEMENT_ADV_ARRIERE = ON;
//                passe_part(2500, 400, MARCHE_ARRIERE, 100, DEBUT_TRAJECTOIRE);
//                passe_part(2650, 550, MARCHE_ARRIERE, 100, MILIEU_TRAJECTOIRE);
//                passe_part(2680, 550, MARCHE_ARRIERE, 100, MILIEU_TRAJECTOIRE);
//                EVITEMENT_ADV_ARRIERE = OFF;
//                passe_part(2720, 550, MARCHE_ARRIERE, 100, FIN_TRAJECTOIRE);
//
//                // calage
//                orienter(180, 30);
//                avancer_reculer(-300, 100);
//                init_X(2890);
//                init_orientation(180);
//
//                // on se pr�pare
//                EVITEMENT_ADV_AVANT = ON;
//                avancer_reculer(200, 100);
//
//                // (on coupe l'�vitement pour la rotation)
//                EVITEMENT_ADV_AVANT = OFF;
//                orienter(0, 30);
//                delay_ms(200);
//
//                // on relache le gobelet
//                pince(GAUCHE, OUVERTE);
//                FLAG_ACTION = NE_RIEN_FAIRE;
//                delay_ms(500);
//                EVITEMENT_ADV_ARRIERE = ON;
//                avancer_reculer(-100, 100);
//
//                //rangement des pinces
//                bras(GAUCHE, FERMER);
//                pince(DROITE, RANGEMENT);
//                pince(GAUCHE, RANGEMENT);
//                delay_ms(500);
//                ascenseur(ARRIERE);
//
//                EVITEMENT_ADV_ARRIERE = OFF;
//                EVITEMENT_ADV_AVANT = ON;
//
//                //direction les marches
//                FLAG_EVITEMENT_STRATEGIQUE = EN_ROUTE_MONTEE_MARCHE;
//                passe_part(2100, 500, MARCHE_AVANT, 60, DEBUT_TRAJECTOIRE);
//                passe_part(1240, 830, MARCHE_AVANT, 60, MILIEU_TRAJECTOIRE);
//                passe_part(1240, 1240, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
//                orienter(90, 100);
//
//            }
//            else // Aucun gobelet = match de merde
//            {
//                //direction les marches direct
//                //direction les marches :
//                bras(GAUCHE, FERMER);
//                pince(DROITE, RANGEMENT);
//                pince(GAUCHE, RANGEMENT);
//                delay_ms(500);
//                ascenseur(ARRIERE);
//
//                //se diriger vers les marches
//                EVITEMENT_ADV_AVANT = ON;
//                FLAG_EVITEMENT_STRATEGIQUE = EN_ROUTE_MONTEE_MARCHE;
//                passe_part(1200, 830, MARCHE_AVANT, 60, DEBUT_TRAJECTOIRE);
//                passe_part(1200, 1240, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
//                orienter(90, 100);
//            }
//        }
//
//        marche();

        
    #endif

        
    #ifdef PETIT_ROBOT
        init_position_robot (153, 1030, 0);
        EVITEMENT_ADV_AVANT = OFF;

        //Init d�part
        init_pinces_jack();
        rejoindre (490, 1030, MARCHE_AVANT, 50);
        cibler(1300, 600, 80);

        while(!SYS_JACK);
        TIMER_90s = ACTIVE;

        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;
        FLAG_ACTION = INIT_PINCES_DEMARRAGE;       

        //Pieds 1
        //rejoindre(1210, 645, MARCHE_AVANT, 100);
        rejoindre(1300, 600, MARCHE_AVANT, 100);
        delay_ms(500);     //1 sec
        //Pieds 2
        //rejoindre (1125, 330, MARCHE_AVANT, 100);
        rejoindre (1100, 230, MARCHE_AVANT, 100);
        delay_ms(4000); // longue tempo pour robot 1
        //Pieds 3
        //rejoindre (935, 570, MARCHE_AVANT, 100);
        rejoindre (870, 665, MARCHE_AVANT, 100);
        EVITEMENT_ADV_AVANT = OFF;
        delay_ms(1600); //1600 : longue tempo pour robot 1
        EVITEMENT_ADV_AVANT = ON;

        //Alignement vers les pieds
        passe_part(600, 200, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
        FLAG_ACTION = FERMETURE_PINCE;
        //Confirmation de l'axe des Y
        EVITEMENT_ADV_ARRIERE = ON;
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(300, 200, MARCHE_ARRIERE, 100, MILIEU_TRAJECTOIRE);
        //on recule jusqu'au pieds
        allumer_pompes();
        passe_part(148, 200, MARCHE_ARRIERE, 50, FIN_TRAJECTOIRE);

        //Danse du cul pour les chopper
        orienter(20, 100);
        orienter(0, 100);
        avancer_reculer(-20, 200);
        //orienter(-20, 200);

        ouvrir_bras(BRAS_GAUCHE);
        FLAG_ACTION = CLAP;
        EVITEMENT_ADV_AVANT = ON;
        EVITEMENT_ADV_ARRIERE = OFF;
        passe_part(200, 160, MARCHE_AVANT, 40, DEBUT_TRAJECTOIRE); // y=170
        //claps
        passe_part(500, 160, MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
        passe_part(890, 160, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);

        //dernier clap
        passe_part(1000, 250, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        fermer_bras(BRAS_GAUCHE);

        //direction depose centre
        passe_part(600, 800, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(460, 1010, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        //r�alignement
        orienter(90, 500);

        //D�pose des pieds
        eteindre_pompe();
        FLAG_ACTION = PIEDS_4; 

        //Sortie zone de d�part
        passe_part(700, 1300, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);

        passe_part (580, 1570, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);

        ////R�cup�ration 4�me pieds
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(400,1770,MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(170, 1770, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        //Aspiration 2 pieds
        allumer_pompes();
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
        FLAG_ACTION = DESACTIVATION_EVITEMENT;
        rejoindre(785, 1745,  MARCHE_ARRIERE, 50);
        EVITEMENT_ADV_ARRIERE = OFF;
        
        /***** Pied un peu chiant **************
        orienter(-90, 15);
        rejoindre(785, 1830, MARCHE_ARRIERE, 25);
        orienter(-70, 50);
        *******************************/

        // Placement zone de d�part
        EVITEMENT_ADV_AVANT = ON;
        rejoindre(700, 1125, MARCHE_AVANT, 100);

        //rentr�e dans la zone de d�part
        EVITEMENT_ADV_AVANT = OFF;
        rejoindre(640, 1090, MARCHE_AVANT, 100);

        //Montage de la tour (d�passement des 350, ejection de la balle
        //descente des pieds pour laisser passer la balle
        angle_AX12(PINCE_HAUT, 555, 1023, SANS_ATTENTE);
        angle_AX12(PINCE_MILIEU, 555, 1023, SANS_ATTENTE);
        angle_AX12(PINCE_BAS, 555, 1023, SANS_ATTENTE);
        delay_ms(1500);

        //on ressert le tout pour que la tour soit bien droite
        pinces(PINCE_HAUT, FERMER);
        pinces(PINCE_MILIEU, FERMER);
        pinces(PINCE_BAS, FERMER);

        //Ejection de la balle
        delay_ms(500);
        //angle_AX12(PINCE_HAUT, 550, 1023, SANS_ATTENTE);
        ejecter_balle();
        delay_ms(500);

        //empilement si n�c�ssaire
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(3000);
        FLAG_ACTION = NE_RIEN_FAIRE;

        //Pieds 5
        rejoindre(550, 1000, MARCHE_AVANT, 100);
        if (COULEUR == VERT)
        {
            orienter (-170, 100);
            orienter(-160, 100);
        }
      
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(3200);
        FLAG_ACTION = NE_RIEN_FAIRE;

        // Pieds 6
        if (COULEUR == JAUNE)
            rejoindre(450, 975, MARCHE_AVANT, 100);
        else
            rejoindre (400, 965, MARCHE_AVANT, 100);
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(2000);

        rejoindre(320, 1000, MARCHE_AVANT, 50);
        FLAG_ACTION = DEPOSE_PIEDS;
        delay_ms(3000);
        //rejoindre(600, 975, MARCHE_ARRIERE, 50);

        avancer_reculer(-150, 100);

        //orienter (0, 20);
        eteindre_pompe();
        
        /******** R�cup gobelet en passe part*/
        /*
        passe_part (1340, 400, MARCHE_ARRIERE, 100, DEBUT_TRAJECTOIRE);
        FLAG_ACTION = ATTRAPE_GOBELET;
        passe_part (910, 1000, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part (910, 1250, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part (360, 1000, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);
        FLAG_ACTION = DEPOSE_GOBELET;*/

        /******* Placement c�t� marche ***

        passe_part (580, 1000, MARCHE_ARRIERE, 100, DEBUT_TRAJECTOIRE);
        passe_part (825, 1260, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        rejoindre(825, 1695, MARCHE_AVANT, 20);*/



       /* while(ETAT_AUTOM != ACCOMPLI);
        delay_ms(3000);
        FLAG_ACTION = DEPOSE_PIEDS;*/
        
                
       
        // passe_part(630, 950, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
       // passe_part(1300, 600, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        //TIMER_DEBUG = DESACTIVE;


        
    #endif
}


void homologation()
{
    COULEUR = couleur_depart();

#ifdef GROS_ROBOT

      // Inits avant d�marage du robot :
        init_jack();

        if (COULEUR == JAUNE)
            synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
        else
            synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);

        while(!SYS_JACK);

        // D�marage du match
        TIMER_90s = ACTIVE;
        EVITEMENT_ADV_AVANT = ON;
        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;

        init_position_robot(180., 988., 0.);
        FLAG_ACTION = INIT_ASCENSEUR;

        delay_ms(1000);

        // Direction Gobelet face zone d�part
        passe_part(620, 988, MARCHE_AVANT, 40, DEBUT_TRAJECTOIRE);
        passe_part(683, 991, MARCHE_AVANT, 40, MILIEU_TRAJECTOIRE);
        passe_part(675, 998, MARCHE_AVANT, 40, MILIEU_TRAJECTOIRE);
        passe_part(742, 1112,MARCHE_AVANT, 40, FIN_TRAJECTOIRE);

        // Direction Gobelet pour lib�rer les deux pieds pour R2
        passe_part(700, 988, MARCHE_AVANT, 40, DEBUT_TRAJECTOIRE);
        if (COULEUR == JAUNE)
            passe_part(650, 600, MARCHE_AVANT, 40, MILIEU_TRAJECTOIRE);
        else
             passe_part(630, 600, MARCHE_AVANT, 40, MILIEU_TRAJECTOIRE);
        passe_part(320, 400, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);


        // Retour au bercail pour d�pose N�1
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
        passe_part(570,455,MARCHE_ARRIERE,40,DEBUT_TRAJECTOIRE);

        FLAG_ACTION = NE_RIEN_FAIRE;
        EVITEMENT_ADV_ARRIERE = OFF;
        EVITEMENT_ADV_AVANT = ON;
        passe_part(550,550,MARCHE_AVANT,40,MILIEU_TRAJECTOIRE);
        passe_part(670,500,MARCHE_AVANT,40,MILIEU_TRAJECTOIRE);
        passe_part(650,990,MARCHE_AVANT,40,MILIEU_TRAJECTOIRE);

        // On d�sactive dans la zone de d�part
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(558, 1040,MARCHE_AVANT,40,MILIEU_TRAJECTOIRE);
        passe_part(270,990,MARCHE_AVANT,40,FIN_TRAJECTOIRE);

        // On v�rifie confirme que le gobelet a bien �t� attrap�
        uint8_t etat_pince_G = LIBRE, etat_pince_D = LIBRE;

        // on enregistrer l'�tat des pinces (remplies ou non)
        if (check_capteur(DROITE) == 0)
            etat_pince_D = FERMER;
        if (check_capteur(GAUCHE) == 0)
            etat_pince_G = FERMER;

        // on d�pose d'abord au centre de la zone si dispo
        if (etat_pince_G == FERMER)
        {
            pince(GAUCHE, OUVERTE);
            etat_pince_G = LIBRE;
        }
        // sinon on d�pose l'autre pince
         if (etat_pince_D == FERMER)
        {
            pince(DROITE, OUVERTE);
            etat_pince_D = LIBRE;
        }

        delay_ms(500);
        avancer_reculer(-100, 50);

        // Pas de gobelet dans les pinces : (si 0 gobelets attrap�s ascensuer d�j� rang� ...)
        pince(GAUCHE, RANGEMENT);
        pince(DROITE, RANGEMENT);
        delay_ms(500);
        ascenseur(ARRIERE);

        passe_part(750, 1000, MARCHE_ARRIERE, 10, DEBUT_TRAJECTOIRE);
        EVITEMENT_ADV_ARRIERE = OFF;
        EVITEMENT_ADV_AVANT = ON;

         passe_part(1200, 830, MARCHE_AVANT, 30, DEBUT_TRAJECTOIRE);
        passe_part(1200, 1240, MARCHE_AVANT, 30, FIN_TRAJECTOIRE);
        orienter(90, 100);

        marche();


        // Strat potentielle si probl�mes �vitement ...
//      // Inits avant d�marage du robot :
//        init_jack();
//
//        if (COULEUR == JAUNE)
//            synchro_AX12(AX_US, 45, 1023, SANS_ATTENTE);
//        else
//            synchro_AX12(AX_US, -45, 1023, SANS_ATTENTE);
//
//        while(!SYS_JACK);
//
//        // D�marage du match
//        TIMER_90s = ACTIVE;
//        EVITEMENT_ADV_AVANT = ON;
//        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;
//
//        init_position_robot(180., 988., 0.);
//        FLAG_ACTION = INIT_ASCENSEUR;
//
//        delay_ms(1000);
//
//        // Direction Gobelet face zone d�part
//        passe_part(620, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
//        passe_part(683, 991, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(675, 998, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(742, 1112,MARCHE_AVANT, 100, FIN_TRAJECTOIRE);
//
//        // Direction Gobelet pour lib�rer les deux pieds pour R2
//        passe_part(700, 988, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
//        if (COULEUR == JAUNE)
//            passe_part(650, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        else
//             passe_part(630, 600, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
//        passe_part(320, 400, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);
//
//
//        // Retour au bercail pour d�pose N�1
//        EVITEMENT_ADV_AVANT = OFF;
//        EVITEMENT_ADV_ARRIERE = ON;
//        passe_part(570,455,MARCHE_ARRIERE,100,DEBUT_TRAJECTOIRE);
//
//        FLAG_ACTION = NE_RIEN_FAIRE;
//        EVITEMENT_ADV_ARRIERE = OFF;
//        EVITEMENT_ADV_AVANT = ON;
//        passe_part(550,550,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//        passe_part(650,800,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//
//        // On d�sactive dans la zone de d�part
//        EVITEMENT_ADV_AVANT = OFF;
//        passe_part(558,990,MARCHE_AVANT,100,MILIEU_TRAJECTOIRE);
//        passe_part(270,990,MARCHE_AVANT,100,FIN_TRAJECTOIRE);
//
//        // On v�rifie confirme que le gobelet a bien �t� attrap�
//        uint8_t etat_pince_G = LIBRE, etat_pince_D = LIBRE, temp1 = 1, temp2 = 1;
//
//        // on enregistrer l'�tat des pinces (remplies ou non)
//        if (check_capteur(DROITE) == 0)
//            etat_pince_D = FERMER;
//        if (check_capteur(GAUCHE) == 0)
//            etat_pince_G = FERMER;
//
//        // on d�pose d'abord au centre de la zone si dispo
//        if (etat_pince_G == FERMER)
//        {
//            pince(GAUCHE, OUVERTE);
//            etat_pince_G = LIBRE;
//        }
//        // sinon on d�pose l'autre pince
//         if (etat_pince_D == FERMER)
//        {
//            pince(DROITE, OUVERTE);
//            etat_pince_D = LIBRE;
//        }
//
//        delay_ms(500);
//        avancer_reculer(-100, 50);
//
//        // Pas de gobelet dans les pinces : (si 0 gobelets attrap�s ascensuer d�j� rang� ...)
//        pince(GAUCHE, RANGEMENT);
//        pince(DROITE, RANGEMENT);
//        delay_ms(500);
//        ascenseur(ARRIERE);
//
//        passe_part(750, 1000, MARCHE_ARRIERE, 50, DEBUT_TRAJECTOIRE);
//        EVITEMENT_ADV_ARRIERE = OFF;
//        EVITEMENT_ADV_AVANT = ON;
//
//         passe_part(1200, 830, MARCHE_AVANT, 60, DEBUT_TRAJECTOIRE);
//        passe_part(1200, 1240, MARCHE_AVANT, 60, FIN_TRAJECTOIRE);
//        orienter(90, 100);
//
//        marche();

#endif

#ifdef PETIT_ROBOT

        init_position_robot (153, 1030, 0);
        EVITEMENT_ADV_AVANT = OFF;

        //Init d�part
        init_pinces_jack();
        rejoindre (490, 1030, MARCHE_AVANT, 50);
        cibler(1300, 600, 80);

        while(!SYS_JACK);
        TIMER_90s = ACTIVE;

        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;
        FLAG_ACTION = INIT_PINCES_DEMARRAGE;

        //Pieds 1
        //rejoindre(1210, 645, MARCHE_AVANT, 100);
        rejoindre(1300, 600, MARCHE_AVANT, 100);
        delay_ms(3500);     //1 sec
        //Pieds 2
        //rejoindre (1125, 330, MARCHE_AVANT, 100);
        rejoindre (1100, 230, MARCHE_AVANT, 100);
        delay_ms(7000); // longue tempo pour robot 1
        //Pieds 3
        //rejoindre (935, 570, MARCHE_AVANT, 100);
        rejoindre (870, 665, MARCHE_AVANT, 100);
        EVITEMENT_ADV_AVANT = OFF;
        delay_ms(2600); //1600 : longue tempo pour robot 1
        EVITEMENT_ADV_AVANT = ON;

        //Alignement vers les pieds
        passe_part(600, 200, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);
        FLAG_ACTION = FERMETURE_PINCE;
        //Confirmation de l'axe des Y
        EVITEMENT_ADV_ARRIERE = ON;
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(300, 200, MARCHE_ARRIERE, 100, MILIEU_TRAJECTOIRE);
        //on recule jusqu'au pieds
        allumer_pompes();
        passe_part(148, 200, MARCHE_ARRIERE, 50, FIN_TRAJECTOIRE);

        //Danse du cul pour les chopper
        orienter(20, 100);
        orienter(0, 100);
        avancer_reculer(-20, 200);
        //orienter(-20, 200);

        ouvrir_bras(BRAS_GAUCHE);
        FLAG_ACTION = CLAP;
        EVITEMENT_ADV_AVANT = ON;
        EVITEMENT_ADV_ARRIERE = OFF;
        passe_part(200, 160, MARCHE_AVANT, 50, DEBUT_TRAJECTOIRE);
        //claps
        passe_part(500, 160, MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
        passe_part(890, 160, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);

        //dernier clap
        passe_part(1000, 250, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        fermer_bras(BRAS_GAUCHE);

        //direction depose centre
        passe_part(600, 800, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(460, 1010, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        //r�alignement
        orienter(90, 500);

        //D�pose des pieds
        eteindre_pompe();
        FLAG_ACTION = PIEDS_4;

        //Sortie zone de d�part
        passe_part(700, 1300, MARCHE_AVANT, 100, DEBUT_TRAJECTOIRE);

        passe_part (580, 1570, MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);

        ////R�cup�ration 4�me pieds
        EVITEMENT_ADV_AVANT = OFF;
        passe_part(400,1770,MARCHE_AVANT, 100, MILIEU_TRAJECTOIRE);
        passe_part(170, 1770, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);

        //Aspiration 2 pieds
        allumer_pompes();
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
        FLAG_ACTION = DESACTIVATION_EVITEMENT;
        rejoindre(785, 1745,  MARCHE_ARRIERE, 50);
        EVITEMENT_ADV_ARRIERE = OFF;

        /***** Pied un peu chiant **************
        orienter(-90, 15);
        rejoindre(785, 1830, MARCHE_ARRIERE, 25);
        orienter(-70, 50);
        *******************************/

        // Placement zone de d�part
        EVITEMENT_ADV_AVANT = ON;
        rejoindre(700, 1125, MARCHE_AVANT, 100);

        //rentr�e dans la zone de d�part
        EVITEMENT_ADV_AVANT = OFF;
        rejoindre(640, 1090, MARCHE_AVANT, 100);

        //Montage de la tour (d�passement des 350, ejection de la balle
        //descente des pieds pour laisser passer la balle
        angle_AX12(PINCE_HAUT, 555, 1023, SANS_ATTENTE);
        angle_AX12(PINCE_MILIEU, 555, 1023, SANS_ATTENTE);
        angle_AX12(PINCE_BAS, 555, 1023, SANS_ATTENTE);
        delay_ms(1500);

        //on ressert le tout pour que la tour soit bien droite
        pinces(PINCE_HAUT, FERMER);
        pinces(PINCE_MILIEU, FERMER);
        pinces(PINCE_BAS, FERMER);

        //Ejection de la balle
        delay_ms(500);
        //angle_AX12(PINCE_HAUT, 550, 1023, SANS_ATTENTE);
        ejecter_balle();
        delay_ms(500);

        //empilement si n�c�ssaire
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(3000);
        FLAG_ACTION = NE_RIEN_FAIRE;

        //Pieds 5
        rejoindre(550, 1000, MARCHE_AVANT, 100);
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(3000);
        FLAG_ACTION = NE_RIEN_FAIRE;

        // Pieds 6
        rejoindre(450, 975, MARCHE_AVANT, 100);
        FLAG_ACTION = ZONE_DEPART;
        delay_ms(2000);

        rejoindre(320, 1000, MARCHE_AVANT, 50);
        FLAG_ACTION = DEPOSE_PIEDS;
        delay_ms(3000);
        //rejoindre(600, 975, MARCHE_ARRIERE, 50);

        avancer_reculer(-150, 100);

        //orienter (0, 20);
        eteindre_pompe();




//        init_position_robot (153, 1030, 0);
//
//        //Init d�part
//        init_pinces_jack();
//        rejoindre (490, 1030, MARCHE_AVANT, 50);
//        cibler(1300, 600, 80);
//
//        while(!SYS_JACK);
//
//        TIMER_90s = ACTIVE;
//        EVITEMENT_ADV_AVANT = ON;
//        init_evitement();
//        STRATEGIE_EVITEMENT = EVITEMENT_NORMAL;
//        FLAG_ACTION = INIT_PINCES_DEMARRAGE;
//
//        //Pieds 1
//        rejoindre(1210, 645, MARCHE_AVANT, 50);
//        delay_ms(4000);     //1 sec
//        //Pieds 2
//        rejoindre (1125, 330, MARCHE_AVANT, 50);
//        delay_ms(5000);
//        //Pieds 3
//        rejoindre (935, 570, MARCHE_AVANT, 50);
//        delay_ms(1000);
//
//        rejoindre (600, 200, MARCHE_AVANT, 50);
//        FLAG_ACTION = FERMETURE_PINCE;
//        //Confirmation de l'axe des Y
//        EVITEMENT_ADV_ARRIERE = ON;
//        EVITEMENT_ADV_AVANT = OFF;
//        rejoindre (300, 200, MARCHE_AVANT, 50);
//        //on recule jusqu'au pieds
//        allumer_pompes();
//        rejoindre(148, 200, MARCHE_ARRIERE, 50);
//
//        //Danse du cul pour les chopper
//        orienter(20, 100);
//        orienter(0, 100);
//        avancer_reculer(-20, 200);
//
//        ouvrir_bras(BRAS_GAUCHE);
//
//        FLAG_ACTION = CLAP;
//        EVITEMENT_ADV_AVANT = ON;
//        EVITEMENT_ADV_ARRIERE = OFF;
//        rejoindre(200, 170, MARCHE_AVANT, 50);
//
//        //claps
//        rejoindre(500, 160, MARCHE_AVANT, 50);
//        rejoindre(890, 160, MARCHE_AVANT, 50);
//
//        //dernier clap
//        rejoindre (1100, 240, MARCHE_AVANT, 50);
//        fermer_bras(BRAS_GAUCHE);
//
//        //direction depose centre
//       rejoindre (600, 800, MARCHE_AVANT, 50);
//       rejoindre (460, 1010, MARCHE_AVANT, 100);
//
//        //r�alignement
//        orienter(90, 500);
//
//        //D�pose des pieds
//        eteindre_pompe();
//        FLAG_ACTION = PIEDS_4;
//
//        //Sortie zone de d�part
//        rejoindre (700, 1300, MARCHE_AVANT, 50);
//
//        rejoindre(580, 1670, MARCHE_AVANT, 50);
//
//        //R�cup�ration 4�me pieds
//        rejoindre(170, 1770, MARCHE_AVANT, 50);
//
//         rejoindre ( 700, 1125, MARCHE_AVANT, 50);
//
//        //rentr�e dans la zone de d�part
//        EVITEMENT_ADV_AVANT = OFF;
//        rejoindre(640, 1090, MARCHE_AVANT, 50);
//
//        //Montage de la tour (d�passement des 350, ejection de la balle
//        //descente des pieds pour laisser passer la balle
//        angle_AX12(PINCE_HAUT, 555, 1023, SANS_ATTENTE);
//        angle_AX12(PINCE_MILIEU, 555, 1023, SANS_ATTENTE);
//        angle_AX12(PINCE_BAS, 555, 1023, SANS_ATTENTE);
//        delay_ms(2000);
//
//        //on ressert le tout pour que la tour soit bien droite
//        pinces(PINCE_HAUT, FERMER);
//        pinces(PINCE_MILIEU, FERMER);
//        pinces(PINCE_BAS, FERMER);
//
//        //Ejection de la balle
//        delay_ms(1000);
//        angle_AX12(PINCE_HAUT, 550, 1023, SANS_ATTENTE);
//        ejecter_balle();
//        delay_ms(4000);
//
//        //empilement si n�c�ssaire
//        FLAG_ACTION = ZONE_DEPART;
//        delay_ms (4000);
//        FLAG_ACTION = NE_RIEN_FAIRE;
//
//        //Pieds 5
//        rejoindre(550, 1000, MARCHE_AVANT, 50);
//        FLAG_ACTION = ZONE_DEPART;
//        delay_ms(3000);
//        FLAG_ACTION = NE_RIEN_FAIRE;
//
//        // Pieds 6
//        rejoindre(450, 975, MARCHE_AVANT, 50);
//        FLAG_ACTION = ZONE_DEPART;
//        delay_ms(3000);
//
//        rejoindre(300, 1000, MARCHE_AVANT, 50);
//        FLAG_ACTION = DEPOSE_PIEDS;
//        delay_ms(3000);
//        rejoindre(500, 1000, MARCHE_ARRIERE, 50);
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
          //orienter(5, 100);




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