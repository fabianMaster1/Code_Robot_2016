/******************************************************************************/
/************** Carte polyvalente Botik  : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: fonctions_deplacements.c
    * Auteur  	: Quentin
    * Revision	: 1.0
    * Date		: 14 d�cembre 2014, 14:29
    *******************************************************************************
    *
    *
******************************************************************************/


/******************************************************************************/
/******************************** INCLUDES ************************************/
/******************************************************************************/

#include "system.h"

/******************************************************************************/
/**************************** FONCTIONS COULEURS ******************************/
/******************************************************************************/

uint8_t couleur_depart()
{
    if (SYS_COULEUR == 0)
        return VERT;
    else
        return VIOLET;
}

double inversion_couleur (double param_inversable)
{
    if (COULEUR == VERT)
        return param_inversable;
    else
        return (- param_inversable);
}


/******************************************************************************/
/********************* FONCTIONS USUELLES (TEST ASSERV) ***********************/
/******************************************************************************/

void trapeze (int8_t sens_marche)
{
    //trap�ze type 8
    //    passe_part (1000, 500, sens_marche, 50, DEBUT_TRAJECTOIRE);
    //    passe_part (1000, 0  , sens_marche, 50, MILIEU_TRAJECTOIRE);
    //    passe_part (0   , 500, sens_marche, 50, MILIEU_TRAJECTOIRE);
    //    passe_part (0   , 0  , sens_marche, 50, FIN_TRAJECTOIRE);
    rejoindre (1000, 500, sens_marche, 100);
    rejoindre (1000, 0  , sens_marche, 100);
    rejoindre (0   , 500, sens_marche, 100);
    rejoindre (0   , 0  , sens_marche, 100);
    orienter(0, 100);
}

void petit_demi_cercle (int8_t sens_marche)
{
    //petit demi cercle
    passe_part (200, 0,    sens_marche, 300, DEBUT_TRAJECTOIRE);
    passe_part (450, 67,   sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (633, 250,  sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (700, 500,  sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (633, 750,  sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (450, 933,  sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (200, 1000, sens_marche, 100, FIN_TRAJECTOIRE);
}

void grand_demi_cercle (int8_t sens_marche)
{
    passe_part (200 , 0   , sens_marche, 500, DEBUT_TRAJECTOIRE);
    passe_part (700 , 134 , sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (1066, 500 , sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (1200, 1000, sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (1066, 1500, sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (700 , 1866, sens_marche, 100, MILIEU_TRAJECTOIRE);
    passe_part (200 , 2000, sens_marche, 100, FIN_TRAJECTOIRE);
}

void carre (int8_t sens_marche)
{
    rejoindre (500, 0  , sens_marche, 100);
    rejoindre (500, 500, sens_marche, 100);
    rejoindre (0  , 500, sens_marche, 100);
    rejoindre (0  , 0  , sens_marche, 100);
    orienter(0, 100);
}

/******************************************************************************/
/******************* FONCTIONS ASSERV HAUT NIVEAU (EVITEMENT) *****************/
/******************************************************************************/


void action_evitement (void)
{
#ifdef GROS_ROBOT
    //Strat�gie alternatives possibles en focntion des �vitements
    EVITEMENT_ADV_AVANT = ON;
    //FLAG_EVITEMENT_STRATEGIQUE = MONTEE_EVITEMENT_EN_COURS;
    //tapis(DROIT, DEPOSE);

    uint8_t presence = 0;

    if (check_capteur(DROIT))
    {
       
    }
    if (check_capteur(DROIT))
    {
        
    }

    if (presence == 1)
    {
        delay_ms(500);
        avancer_reculer(-100, 100);
        delay_ms (500);
    }


     //alignement aux marches
    if (get_X() > 2000)
    {
        plus_court(2000, 900, MARCHE_AVANT, 70, rej, 0);
    }
    if (get_X() > 1200)
    {
         plus_court(1200, 830, MARCHE_AVANT, 70, rej, 0);
    }

    if (COULEUR == VIOLET)
        plus_court(1200, 1240, MARCHE_AVANT, 70, rej, 0);
    else
        plus_court(1240, 1240, MARCHE_AVANT, 70, rej, 0);


    // on s'aligne puis on monte
    orienter(90, 100);
    
    while(1);
#endif 
}


uint16_t compt_evitement = 0; //Permet de connaitre le nombre de fois qu'on a eu le m�me �vitement
                                    //Reset � chaque d�but d'�tape
void delai_action(void)
{  
    static uint8_t tempo = 0;
        
    //TIMER_10ms = DESACTIVE;
    
    switch(FLAG_ACTION)
    {//Mettre toutes les fonction de backup strat
        case TOUR_ALLIE:
            if(ETAPE_TOUR_ALLIE == 0)
            {//positionne vers la barre, s'encastre dedant
//                EVITEMENT_ADV_AVANT = OFF;
//                EVITEMENT_ADV_ARRIERE = ON;
//                
//                rejoindre(200, 1000, MARCHE_ARRIERE, 50);
//                
//                //Range les pinces si on change de strat
//                angle_AX12(PINCE_D, 405, 300, SANS_ATTENTE); //Position rang�
//                angle_AX12(PINCE_G, 860, 300, SANS_ATTENTE); //Position rang�
//                
//                FLAG_ACTION = POISSONS;
            }

            else if(ETAPE_TOUR_ALLIE == 1)
            {//attrappe tour et recule (sort de la barre)
                compt_evitement++;
                if(compt_evitement > 250)
                {
                    compt_evitement = 0;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    rejoindre(895, 1450, MARCHE_ARRIERE, 5);
                    orienter(140, 5);
                    ETAPE_TOUR_ALLIE = 2;
                }
            }

            else if(ETAPE_TOUR_ALLIE == 2)
            {//Ferme les portes des cabines
                
                
                //POUR HOMOLOGATION
                /************************************/
                /*
                if(EVITEMENT_ADV_ARRIERE == ON)
                {//2 cas en fonction qu'il soit en marche avant ou marche arri�re 
                    //EVITEMENT_ADV_AVANT = OFF;
                    //EVITEMENT_ADV_ARRIERE = OFF;
                    //orienter(95, 50);
                    //EVITEMENT_ADV_AVANT = ON;
                    
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    
                    rejoindre(300, 1600, MARCHE_AVANT, 30);//On va � la cache 1
                    //delay_ms(2000);
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    
                    //Relance un peu les pinces pour pas qu'elles laches
                    attrapper_cubes();
                    
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = ON;
                    rejoindre(350, 1000, MARCHE_ARRIERE, 50);//on reprend ce qu'on fesait
                }

                else
                {//Si on rencontre quelqu'un en allant se cacher
                    //Alors on fini l'�tape 2 et on passe � la 3
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = ON;
                    rejoindre(350, 1000, MARCHE_ARRIERE, 50);//on reprend ce qu'on fesait
                    //Relance un peu les pinces pour pas qu'elles laches
                    angle_AX12(PINCE_D, 975, 850, SANS_ATTENTE); //Position o� il attrappe
                    angle_AX12(PINCE_G, 290, 850, SANS_ATTENTE); //Positions o� il attrappe
                }
                 * */
                /************************************/
            }

            else if(ETAPE_TOUR_ALLIE == 3)
            {//avance, va dans la zone de largage, pose la tour
                //compteur_evitement++;
                if(EVITEMENT_ADV_ARRIERE == ON)
                {   //On d�sactive tout pour qu'il reparte en avant
                    EVITEMENT_ADV_AVANT = ON;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    
                    //Relance un peu les pinces pour pas qu'elles laches
                    attrapper_cubes();
                    
                    rejoindre(1000, 1000, MARCHE_AVANT, 90);
                    ETAPE_TOUR_ALLIE = 4;
                }
                
                else
                {
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = ON;

                    //Relance un peu les pinces pour pas qu'elles laches
                    attrapper_cubes();

                    rejoindre(400, 1000, MARCHE_ARRIERE, 40);//On recule pour liberer le robot adverse
                    
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 4);

                    EVITEMENT_ADV_AVANT = ON;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    
                    rejoindre(1000, 1000, MARCHE_AVANT, 90);
                    ETAPE_TOUR_ALLIE = 4;
                    //if(compteur_evitement > 10)//Si on a trop fait de fois des all�s retour
                        //FLAG_ACTION = POISSONS;
                }
            }

            else if(ETAPE_TOUR_ALLIE == 4)
            {//recule pour ne pas renverser la tour
                compt_evitement++;
                
                if(compt_evitement > 250)
                {
                    compt_evitement = 0;
                    ranger_pinces();
                    ETAPE_POISSONS = 10;
                    FLAG_ACTION = POISSONS;
                }
            }
            
            
            else if(ETAPE_TOUR_ALLIE == 5)
            {//Range les pinces
                
            }
            break;


        case TOUR_ADVERSAIRE:
			if (ETAPE_TOUR_ADVERSAIRE == 0)
            {//positionne vers la barre, s'encastre dedant
                EVITEMENT_ADV_AVANT = OFF;
                delay_ms(17);
                EVITEMENT_ADV_ARRIERE = OFF;
                delay_ms(17);
                
                rejoindre(800, 1500, MARCHE_ARRIERE, 50);
                FLAG_ACTION = TOUR_ALLIE;
            }

			else if (ETAPE_TOUR_ADVERSAIRE == 1)
            {//attrappe tour et recule (sort de la barre)
                compt_evitement++;
                if(compt_evitement > 250)
                {
                    compt_evitement = 0;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    delay_ms(10);
                    rejoindre(2130, 1500, MARCHE_ARRIERE, 5);
                    orienter(0, 5);
                    ETAPE_TOUR_ADVERSAIRE = 2;
                }
            }

			else if (ETAPE_TOUR_ADVERSAIRE == 2)
            {//recule encore, se positionne pour poser la tour
                compt_evitement++;
                if(compt_evitement > 250)
                {
                    compt_evitement = 0;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    rejoindre(2130, 1450, MARCHE_ARRIERE, 5);
                    orienter(140, 5);
                    ETAPE_TOUR_ADVERSAIRE = 3;
                }
            }

			else if (ETAPE_TOUR_ADVERSAIRE == 3)
            {//avance, va dans la zone de largage, pose la tour
                  //On d�sactive tout pour qu'il reparte en avant
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;
                    delay_ms(7);
                    //Relance un peu les pinces pour pas qu'elles laches
//                    attrapper_cubes();
                    
                    avancer_reculer(100, 30);
//                    rejoindre(1000, 1000, MARCHE_AVANT, 90);
                    ETAPE_TOUR_ALLIE = 4;
//                
//                else
//                {
//                    EVITEMENT_ADV_AVANT = OFF;
//                    EVITEMENT_ADV_ARRIERE = ON;
//
//                    //Relance un peu les pinces pour pas qu'elles laches
//                    attrapper_cubes();
//
//                    rejoindre(400, 1000, MARCHE_ARRIERE, 40);//On recule pour liberer le robot adverse
//                    
//                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
//                    while((COMPTEUR_TEMPS_MATCH - tempo) < 4);
//
//                    EVITEMENT_ADV_AVANT = ON;
//                    EVITEMENT_ADV_ARRIERE = OFF;
//                    
//                    rejoindre(1000, 1000, MARCHE_AVANT, 90);
//                    ETAPE_TOUR_ALLIE = 4;
//                    //if(compteur_evitement > 10)//Si on a trop fait de fois des all�s retour
//                        //FLAG_ACTION = POISSONS;
//                }
            }
            
			else if (ETAPE_TOUR_ADVERSAIRE == 4)
            {//recule pour ne pas renverser la tour
//                compt_evitement++;
//                
//                if(compt_evitement > 250)
//                {
//                    compt_evitement = 0;
//                    ranger_pinces();
//                    ETAPE_POISSONS = 10;
//                    FLAG_ACTION = POISSONS;
//                }
            }
            break;
            
            
        case PORTES:
            if(ETAPE_PORTES == 0)
            {
                
            }
            
            if(ETAPE_PORTES == 1)
            {
                
//                rejoindre(600, 1800, MARCHE_AVANT, 30);
                
                compt_evitement++;
                
                if(compt_evitement > 250)
                {
                    EVITEMENT_ADV_ARRIERE = OFF;
                    delay_ms(7);
                    compt_evitement = 0;
                    rejoindre(320, 1500, MARCHE_ARRIERE, 5);
                    ETAPE_PORTES = 2;
                }
            }
            
            if(ETAPE_PORTES == 2)
            {
                
            }
            
            if(ETAPE_PORTES == 3)
            {
                EVITEMENT_ADV_ARRIERE = OFF;
                delay_ms(7);
            }
            
            if(ETAPE_PORTES == 4)
            {
//                
//                rejoindre(600, 1860, MARCHE_AVANT, 30);
                
                compt_evitement++;
                
                if(compt_evitement > 250)
                {
                    EVITEMENT_ADV_ARRIERE = OFF;
                    compt_evitement = 0;
                    rejoindre(320, 1500, MARCHE_ARRIERE, 5);
                    FLAG_ACTION = TOUR_ALLIE;
                }
            }
            break;
            

        case POISSONS:
            if(COULEUR == VERT)//Signifie VIOLET
            {
                if(ETAPE_POISSONS == 10)
                {
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = ON;
                    delay_ms(10);

                    rejoindre(1000, 800, MARCHE_ARRIERE, 40);         //A CHECKER!!!!!!!!!!
                }

                else if(ETAPE_POISSONS == 11)
                {
                    if(get_X() < 650)
                        EVITEMENT_ADV_AVANT = OFF;
                }

                if(ETAPE_POISSONS == 0)
                {//avance vers le le bac � poissons
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;
//                    rejoindre(800, 1000, MARCHE_AVANT, 60);
                    avancer_reculer(150, 50);

                    compteur_evitement++;
                    if(compteur_evitement > 250)
                    {
                        EVITEMENT_ADV_ARRIERE = OFF;
                        delay_ms(17);
                    }
                    /*
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;

                    rejoindre(1200, 800, MARCHE_ARRIERE, 50);//On va � la chache 2
                    //delay_ms(2000);
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 3 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    */
                }


                else if(ETAPE_POISSONS == 1)
                {//avance vers le le bac � poissons
                    compteur_evitement++;
                    if(compteur_evitement > 250)
                    {
                        EVITEMENT_ADV_ARRIERE = OFF;
                        delay_ms(17);
                    }
                }


                else if(ETAPE_POISSONS == 2)
                {

                }


                else if(ETAPE_POISSONS == 3)
                {//on sort le filet
                    //Rien � faire car on ne bouge pas
                }


                else if(ETAPE_POISSONS == 4)
                {//on recule un peu
                    //Alors avance pour laisser passer le robot (vers le bas du terrain)
                    if(EVITEMENT_ADV_ARRIERE == ON)
                    {  //Si on est entrain de reculer alors n avance un peu

                        EVITEMENT_ADV_AVANT = OFF;  //On d�sactive l'�vitement car il n'y a pas la place pour un robot adverse
                        EVITEMENT_ADV_ARRIERE = OFF;

                        rejoindre(450, 150, MARCHE_AVANT, 50);//On avance un peu pour d�gager la place

                        tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                        while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    }

                    else
                    {//Si on a eu un �vitement pendant a backup strat alors on repart sur la strat d'avant
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = ON;
                        rejoindre(640, 150, MARCHE_ARRIERE, 60);//On se place pr�s du bac
                    }
                }

                else if(ETAPE_POISSONS == 5)
                {//On positionne le filet dans le bac

                }

                else if (ETAPE_POISSONS == 6)
                {//On avance dans le bac et on remonte le filet (on g�re les cas d'impossibilit� de remonter)
                    //Alors on se d�place dans le bac
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;

                    rejoindre(640, 150, MARCHE_AVANT, 60);//On se place pr�s du bac
                    //delay_ms(2000);
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                }


                else if (ETAPE_POISSONS == 7)
                {//�vite la barre de de la zone de largage des poissons, d�pose les poissons
                    //2 cas en fonction de si on est d�j� en �vitement
                    if(EVITEMENT_ADV_ARRIERE == ON)
                    {
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        orienter(180,100);//R�oriente bien parall�le � la bordure

                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        avancer_reculer(250, 60);  //avance un peu pour d�gager le passage

                        tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                        while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    }
                    else if(EVITEMENT_ADV_AVANT == ON)
                    {//Si on � un �vitement avant alors il y a quelqu'un l� o� on voulait se d�gager donc on reprend ce qu'on faisait
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        orienter(180,100);//R�oriente bien parall�le � la bordure

                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = ON;

                        rejoindre(1100, 250, MARCHE_ARRIERE, 50);
                    }
                }


                else if (ETAPE_POISSONS == 8)
                {

                }
            }
            
            /*******************************************************************************************************************/
            /*******************************************************************************************************************/
            /*******************************************************************************************************************/
            /*******************************************************************************************************************/
            
            if(COULEUR == VIOLET)   //Signifie VERT
            {
//                if(ETAPE_POISSONS == 10)
//                {
//                EVITEMENT_ADV_AVANT = OFF;
//                EVITEMENT_ADV_ARRIERE = ON;
//                delay_ms(10);
//                
//                rejoindre(1000, 800, MARCHE_ARRIERE, 40);         //A CHECKER!!!!!!!!!!
//                }
//            
//                else if(ETAPE_POISSONS == 11)
//                {
//                    if(get_X() < 650)
//                        EVITEMENT_ADV_AVANT = OFF;
//                }
            
                if(ETAPE_POISSONS == 0)
                {//avance vers le le bac � poissons
                    EVITEMENT_ADV_AVANT = OFF;
                    delay_ms(7);
                    EVITEMENT_ADV_ARRIERE = OFF;
                    delay_ms(7);
                    avancer_reculer(-50, 30);
//                    rejoindre(800, 1000, MARCHE_AVANT, 60);
//
//                    compteur_evitement++;
//                if(compteur_evitement > 250)
//                {
//                    if(COULEUR == VERT) //SIgnifie Violet
//                        EVITEMENT_ADV_ARRIERE = OFF;
//                    if(COULEUR == VIOLET) //SIgnifie VERT
//                        EVITEMENT_ADV_AVANT = OFF;
//                    delay_ms(17);
//                }

                    /*
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;

                    rejoindre(1200, 800, MARCHE_ARRIERE, 50);//On va � la chache 2
                    //delay_ms(2000);
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 3 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    */
                }
            
            
                else if(ETAPE_POISSONS == 1)
                {//avance vers le le bac � poissons

                }


                else if(ETAPE_POISSONS == 2)
                {

                }


                else if(ETAPE_POISSONS == 3)
                {//on sort le filet
                    //Rien � faire car on ne bouge pas
                }


                else if(ETAPE_POISSONS == 4)
                {//on recule un peu
                    //Alors avance pour laisser passer le robot (vers le bas du terrain)
                    if(EVITEMENT_ADV_ARRIERE == ON)
                    {  //Si on est entrain de reculer alors avance un peu
                        EVITEMENT_ADV_AVANT = OFF;  //On d�sactive l'�vitement car il n'y a pas la place pour un robot adverse
                        EVITEMENT_ADV_ARRIERE = OFF;

//                        rejoindre(330, 180, MARCHE_ARRIERE, 50);
                        avancer_reculer(-100, 30);

                        tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                        while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    }

                    else
                    {//Si on a eu un �vitement pendant a backup strat alors on repart sur la strat d'avant
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        rejoindre(640, 160, MARCHE_AVANT, 60);//On se place pr�s du bac
                    }
                }

                else if(ETAPE_POISSONS == 5)
                {//On positionne le filet dans le bac

                }

                else if (ETAPE_POISSONS == 6)
                {//On avance dans le bac et on remonte le filet (on g�re les cas d'impossibilit� de remonter)
                    //Alors on se d�place dans le bac
                    EVITEMENT_ADV_AVANT = OFF;
                    EVITEMENT_ADV_ARRIERE = OFF;

                    rejoindre(640, 160, MARCHE_ARRIERE, 40);//On se place pr�s du bac
                    //delay_ms(2000);
                    tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                    while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                }


                else if (ETAPE_POISSONS == 7)
                {//�vite la barre de de la zone de largage des poissons, d�pose les poissons
                    //2 cas en fonction de si on est d�j� en �vitement
                    if(EVITEMENT_ADV_ARRIERE == ON)
                    {
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        orienter(0,100);//R�oriente bien parall�le � la bordure

                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        avancer_reculer(-250, 40);  //avance un peu pour d�gager le passage

                        tempo = COMPTEUR_TEMPS_MATCH;//Lance un timer de 2 sec pour attendre un peu avant de r�essayer
                        while((COMPTEUR_TEMPS_MATCH - tempo) < 2);
                    }
                    else if(EVITEMENT_ADV_AVANT == ON)
                    {//Si on � un �vitement avant alors il y a quelqu'un l� o� on voulait se d�gager donc on reprend ce qu'on faisait
                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = OFF;
                        orienter(0,100);//R�oriente bien parall�le � la bordure

                        EVITEMENT_ADV_AVANT = OFF;
                        EVITEMENT_ADV_ARRIERE = ON;

                        avancer_reculer(-250, 40);
                    }
                }


                else if (ETAPE_POISSONS == 8)
                {

                }
            }
            
            break;

            
        case DEFONCER_DUNE:
            EVITEMENT_ADV_AVANT = OFF;
            EVITEMENT_ADV_ARRIERE = OFF;
            delay_ms(11);
            rejoindre(800, 1400,MARCHE_ARRIERE, 70);
            
            FLAG_ACTION = TOUR_ALLIE;
            break;

        case COQUILLAGES:
            break;

            
        default:
            break;
    }
    
    //TIMER_10ms = ACTIVE;
    fin_strategie_cause_evitement = 1;//Activation du Flag qui bloque les d�placement dut � la backup strat
}


void cibler (double x, double y, double pourcentage_vitesse)
{
    if(fin_strategie_cause_evitement == 0)
    {
        uint8_t erreur = _cibler (x, y, pourcentage_vitesse);
        if (erreur == EVITEMENT)
        {
            if(STRATEGIE_EVITEMENT == ACTION_EVITEMENT)
            {
                //action_evitement();
                delai_action();
            }
            else if(STRATEGIE_EVITEMENT == EVITEMENT_NORMAL)
            {
                //action en cas d'�vitements
                cibler(x,y,pourcentage_vitesse);
            }
            else if(STRATEGIE_EVITEMENT == DELAI_ACTION)
            {
                delai_action();
            }
        }
        else if (erreur == BLOCAGE)
        {
            //Actions a faire en cas de blocage
        }
    }
}

void orienter (double angle, double pourcentage_vitesse)
{
    if(fin_strategie_cause_evitement == 0)
    {
        uint8_t erreur = _orienter (angle, pourcentage_vitesse);
        if ( erreur == EVITEMENT)
        {
            if (STRATEGIE_EVITEMENT == ACTION_EVITEMENT)
            {
                action_evitement();
            }
            else if (STRATEGIE_EVITEMENT == EVITEMENT_NORMAL)
            {
                //action en cas d'�vitements
                orienter ( angle, pourcentage_vitesse);
            }
            else if(STRATEGIE_EVITEMENT == DELAI_ACTION)
            {
                delai_action();
            }
        }
        else if (erreur == BLOCAGE)
        {
            //Actions a faire en cas de blocage
        }
    }
}

void rejoindre (double x, double y, int8_t sens_marche, double pourcentage_vitesse)
{
    if(fin_strategie_cause_evitement == 0)
    {
        uint8_t erreur = _rejoindre (x, y, sens_marche, pourcentage_vitesse);
        if ( erreur == EVITEMENT)
        {
            if (STRATEGIE_EVITEMENT == ACTION_EVITEMENT)
            {
                action_evitement();
            }
            else if (STRATEGIE_EVITEMENT == EVITEMENT_NORMAL)
            {
                plus_court(x,y,sens_marche,pourcentage_vitesse,rej,1);
            }
            else if(STRATEGIE_EVITEMENT == DELAI_ACTION)
            {
                delai_action();
            }
        }
        else if (erreur == BLOCAGE)
        {
            //Actions a faire en cas de blocage
        }  
    }
}

void avancer_reculer (double distance, double pourcentage_vitesse)
{
    if(fin_strategie_cause_evitement == 0)
    {
        uint8_t erreur = _avancer_reculer (distance, pourcentage_vitesse);
        if ( erreur == EVITEMENT)
        {
            if (STRATEGIE_EVITEMENT == ACTION_EVITEMENT)
            {
                action_evitement();
            }
            else if (STRATEGIE_EVITEMENT == EVITEMENT_NORMAL)
            {
                //action en cas d'�vitements
            }
            else if(STRATEGIE_EVITEMENT == DELAI_ACTION)
            {
                delai_action();
            }
        }
        else if (erreur == BLOCAGE)
        {

            //Actions a faire en cas de blocage
        }
    }
}

void passe_part (double x, double y, int8_t sens_marche, double pourcentage_vitesse, char last)
{
    if(fin_strategie_cause_evitement == 0)
    {
        uint8_t erreur = _passe_part (x, y, sens_marche, pourcentage_vitesse, last);
        if ( erreur == EVITEMENT)
        {
            if (STRATEGIE_EVITEMENT == ACTION_EVITEMENT)
            {
                action_evitement();
            }
            else if (STRATEGIE_EVITEMENT == EVITEMENT_NORMAL)
            {
                plus_court(x,y,sens_marche,pourcentage_vitesse,last,1);
            }
            else if(STRATEGIE_EVITEMENT == DELAI_ACTION)
            {
                delai_action();
            }
        }
        else if (erreur == BLOCAGE)
        {
            //Actions a faire en cas de blocage
        }
    }
}



/******************************************************************************/
/***************** FONCTIONS ASSERV BAS NIVEAU (config asserv) ****************/
/******************************************************************************/

uint8_t _cibler (double x, double y, double pourcentage_vitesse)
{
    y = inversion_couleur(y);
    FLAG_ASSERV.brake = OFF;
    //delay_ms(10);

    reinit_asserv();

    x *= TICKS_PAR_MM;
    y *= TICKS_PAR_MM;

    TYPE_CONSIGNE = MM;

    if ((y - Y.actuelle) != 0 || (x - X.actuelle) != 0 )//&& (Y.consigne - Y.actuelle) != 0)
    {
        ORIENTATION.consigne =  atan2((y - Y.actuelle), (x - X.actuelle)) * ENTRAXE_TICKS/2 ;

        calcul_vitesse_orientation(pourcentage_vitesse);
        calcul_acceleration_orientation();

        FLAG_ASSERV.position = OFF;
        FLAG_ASSERV.orientation = ON;
        FLAG_ASSERV.vitesse = ON;

        FLAG_ASSERV.type_deplacement = ORIENTER;

        FLAG_ASSERV.etat_angle = EN_COURS;
        FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
        FLAG_ASSERV.immobilite = 0;

        FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;

        while(FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    }
    return FLAG_ASSERV.erreur;
}

uint8_t _orienter (double angle, double pourcentage_vitesse)
{
    angle = inversion_couleur(angle);
    FLAG_ASSERV.brake = OFF;
    //delay_ms(10);

    reinit_asserv();

    TYPE_CONSIGNE = MM;

    ORIENTATION.consigne = (angle * Pi)/ 180 * (ENTRAXE_TICKS/2);

    calcul_vitesse_orientation(pourcentage_vitesse);
    calcul_acceleration_orientation();

    FLAG_ASSERV.position = OFF;
    FLAG_ASSERV.orientation = ON;
    FLAG_ASSERV.vitesse = ON;

    FLAG_ASSERV.type_deplacement = ORIENTER;

    FLAG_ASSERV.etat_angle = EN_COURS;
    FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
    FLAG_ASSERV.immobilite = 0;

    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;

    while(FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    return FLAG_ASSERV.erreur;
}

void faire_des_tours (int nb_tour)
{
    int i;
    double j;

    if (nb_tour < 0)
    {
        nb_tour *= -1;
        j = -1.;
    }
    else
        j= 1.;

    _fdt (120 * j  , DEBUT_TRAJECTOIRE);
    for (i = 0 ; i < nb_tour - 1 ; i++)
    {
        _fdt(- 120 * j, MILIEU_TRAJECTOIRE);
        _fdt (0,  MILIEU_TRAJECTOIRE);
        _fdt (120 * j, MILIEU_TRAJECTOIRE);
    }

    _fdt (- 120 * j, MILIEU_TRAJECTOIRE);
    _fdt (0, FIN_TRAJECTOIRE);
}

void _fdt (double angle, char last)
{
    if (last == DEBUT_TRAJECTOIRE)
    {
        FLAG_ASSERV.brake = OFF;
        // delay_ms(10);
        reinit_asserv();

        TYPE_CONSIGNE = MM;
    }

    angle = inversion_couleur(angle);

    ORIENTATION.consigne = (angle * Pi)/ 180 * (ENTRAXE_TICKS/2);

#ifdef PETIT_ROBOT
    VITESSE_MAX_ORIENTATION = VITESSE_ANGLE_PAS;
    acc.acceleration.orientation = ACC_ORIENTATION_CONSIGNE;
    acc.deceleration.orientation = DCC_ORIENTATION_CONSIGNE;
#endif
#ifdef GROS_ROBOT
    VITESSE_MAX_ORIENTATION = VITESSE_ANGLE_PAS;
    calcul_acceleration_orientation();
#endif

    FLAG_ASSERV.position = OFF;
    FLAG_ASSERV.orientation = ON;
    FLAG_ASSERV.vitesse = ON;
    FLAG_ASSERV.phase_deceleration_distance = PHASE_NORMAL;
    FLAG_ASSERV.phase_decelaration_orientation = PHASE_NORMAL;

    FLAG_ASSERV.type_deplacement = FAIRE_DES_TOURS;
    FLAG_ASSERV.etat_angle = EN_COURS;
    FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;

    FLAG_ASSERV.immobilite = 0;

    if (last == FIN_TRAJECTOIRE)
        FLAG_ASSERV.vitesse_fin_nulle = ON;
    else
        FLAG_ASSERV.vitesse_fin_nulle = OFF;

    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;
    while (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
}

uint8_t _rejoindre (double x, double y, int8_t sens_marche, double pourcentage_vitesse)
{
    y = inversion_couleur(y);
    FLAG_ASSERV.brake = OFF;
    //delay_ms(10);

    reinit_asserv();

    X.consigne = x * TICKS_PAR_MM;
    Y.consigne = y * TICKS_PAR_MM;

    TYPE_CONSIGNE = XY;

    FLAG_ASSERV.sens_deplacement = sens_marche;

    calcul_vitesse_position(pourcentage_vitesse);
    calcul_acceleration_position();

    
#ifdef PETIT_ROBOT
    VITESSE_MAX_ORIENTATION = VITESSE_ANGLE_PAS;
    acc.acceleration.orientation = DCC_ORIENTATION_CONSIGNE;
    acc.deceleration.orientation = DCC_ORIENTATION_CONSIGNE;
#else
    VITESSE_MAX_ORIENTATION = VITESSE_ANGLE_PAS / 2;
    calcul_acceleration_orientation();
#endif


    FLAG_ASSERV.position = ON;
    FLAG_ASSERV.orientation = ON;
    FLAG_ASSERV.vitesse = ON;

    FLAG_ASSERV.etat_angle = EN_COURS;
    FLAG_ASSERV.etat_distance = EN_COURS;
    FLAG_ASSERV.type_deplacement = AVANCER;
    FLAG_ASSERV.vitesse_fin_nulle = ON;

    FLAG_ASSERV.immobilite = 0;


    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;
    while (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    return FLAG_ASSERV.erreur;
}

uint8_t _avancer_reculer (double distance, double pourcentage_vitesse)
{
    FLAG_ASSERV.brake = OFF;
    reinit_asserv();

    TYPE_CONSIGNE = MM;

    DISTANCE.consigne = distance * (TICKS_PAR_MM);

    if (distance < 0.)
        FLAG_ASSERV.sens_deplacement = MARCHE_ARRIERE;
    else
        FLAG_ASSERV.sens_deplacement = MARCHE_AVANT;

    calcul_vitesse_position(pourcentage_vitesse);
    calcul_acceleration_position();

    FLAG_ASSERV.position = ON;
    FLAG_ASSERV.orientation = OFF;
    FLAG_ASSERV.vitesse = ON;
    FLAG_ASSERV.vitesse_fin_nulle = ON;

    FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
    FLAG_ASSERV.etat_distance = EN_COURS;
    FLAG_ASSERV.immobilite = 0;

    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;
    while (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    return FLAG_ASSERV.erreur;
}

uint8_t _calage (double distance, double pourcentage_vitesse)
{
    FLAG_ASSERV.brake = OFF;
    reinit_asserv();

    TYPE_CONSIGNE = MM;

    DISTANCE.consigne = distance * (TICKS_PAR_MM);

    if (distance < 0.)
        FLAG_ASSERV.sens_deplacement = MARCHE_ARRIERE;
    else
        FLAG_ASSERV.sens_deplacement = MARCHE_AVANT;

    calcul_vitesse_position(pourcentage_vitesse);
    calcul_acceleration_position();

    FLAG_ASSERV.position = ON;
    FLAG_ASSERV.orientation = OFF;
    FLAG_ASSERV.vitesse = ON;
    FLAG_ASSERV.vitesse_fin_nulle = ON;

    FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
    FLAG_ASSERV.etat_distance = EN_COURS;
    FLAG_ASSERV.immobilite = 0;
    PID.VITESSE_DIS.max_I = MAX_ERREUR_INTEGRALLE_V / 10;
    PID.VITESSE_DIS.seuil_immobilite = SEUIL_IMMOBILITE /10;

    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;
    while (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    return FLAG_ASSERV.erreur;
}

uint8_t _passe_part (double x, double y, int8_t sens_marche, double pourcentage_vitesse, char last)
{
    if (last == DEBUT_TRAJECTOIRE)
    {
        FLAG_ASSERV.brake = OFF;
        //  delay_ms(10);
        reinit_asserv();

        TYPE_CONSIGNE = XY;
    }

    y = inversion_couleur(y);
    X.consigne = x * TICKS_PAR_MM;
    Y.consigne = y * TICKS_PAR_MM;

    calcul_vitesse_position(pourcentage_vitesse);
    calcul_acceleration_position();

    VITESSE_MAX_ORIENTATION = VITESSE_ANGLE_PAS;
    acc.acceleration.orientation = ACC_ORIENTATION_CONSIGNE;
    acc.deceleration.orientation = DCC_ORIENTATION_CONSIGNE;

    //FLAG_ASSERV.erreur = DEPLACEMENT_NORMAL;
    FLAG_ASSERV.position = ON;
    FLAG_ASSERV.orientation = ON;
    FLAG_ASSERV.vitesse = ON;
    FLAG_ASSERV.sens_deplacement = sens_marche;
    FLAG_ASSERV.phase_deceleration_distance = PHASE_NORMAL;
    FLAG_ASSERV.phase_decelaration_orientation = PHASE_NORMAL;

    FLAG_ASSERV.type_deplacement = PASSE_PART;
    FLAG_ASSERV.etat_angle = EN_COURS;
    FLAG_ASSERV.etat_distance = EN_COURS;

    FLAG_ASSERV.immobilite = 0;

    if (last == FIN_TRAJECTOIRE)
        FLAG_ASSERV.vitesse_fin_nulle = ON;
    else
        FLAG_ASSERV.vitesse_fin_nulle = OFF;

    FLAG_ASSERV.fin_deplacement = DEBUT_DEPLACEMENT;
    while (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT);
    return FLAG_ASSERV.erreur;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/*
    * repere du terrain => 0:0 en bas a gauche quand on fait face au robotmovie (jaune a gauche et vert � droite)
    * repere de la matrice => 0:0 en haut a gauche quand on fait face au robotmovie (jaune a gauche et vert � droite)
    *
    * direction et repere dans le terrain
    * 812 1 => y+1
    * 703 5 => y-1
    * 654 3 => x+1
    *
    *
    * direction dans la matrice
    *    654
    *    703
    *    812
    *
    * direction de longement : on se d�place suivant la fl�che et on observe la case ou est le num�ro
    * par exemple si on a 3, on ira vers le haut du terrain et on testera si notre gauche est libre
    * 1 | 2  3 ^ 4    6     8
    *   |      |    -->     <--
    *   V      |      5     7
    *

*/



void deplacement(int8_t sens_marche,double pourcentage_deplacement,char last) //transforme les points en commandes de deplacements
{
    int i=1;
    int id = id_evitement;
    int evit_avant=EVITEMENT_ADV_AVANT;
    int evit_arriere=EVITEMENT_ADV_ARRIERE;

#ifdef ORDI
    if(itineraire_court[i][0] != -1);
    cout << "cibler("<<(double)(itineraire_court[i][0]*100)+50<<","<<(double)((itineraire_court[i][1])*100)+50<<","<<pourcentage_deplacement<<")"<<endl;

    while(i<curseur && id == id_evitement && itineraire_court[i][0] != -1 )//affiche l'itineraire
    {
        if(last == rej)
        {
            cout << "rejoindre("<<(double)(itineraire_court[i][0]*100)+50<<","<<(double)((itineraire_court[i][1])*100)+50<<","<<sens_marche<<","<<pourcentage_deplacement<<")"<<endl;
        }
        else
        {
            if(i == 0)
            {
                last = DEBUT_TRAJECTOIRE;
            }
            else
            {
                last = MILIEU_TRAJECTOIRE;
            }
            cout << "passe_part("<<(double)(itineraire_court[i+1][0]*100)+50<<","<<(double)((itineraire_court[i+1][1])*100)+50<<","<<sens_marche<<","<<pourcentage_deplacement<<","<<last<<")"<<endl;
        }
        i++;
    }
#else
    //permet le cibler sans probleme
    EVITEMENT_ADV_ARRIERE = OFF;
    EVITEMENT_ADV_AVANT = OFF;
    DETECTION = OFF;

     //PutsUART(UART_XBEE,"\n\ron va cibler\n\r");


    if(itineraire_court[i][0] != -1);
    cibler((double)(itineraire_court[i][0]*100)+50,(double)((itineraire_court[i][1])*100)+50,pourcentage_deplacement);

    //on remet l'evitement
    EVITEMENT_ADV_ARRIERE = evit_arriere;
    EVITEMENT_ADV_AVANT = evit_avant;
    DETECTION = OFF;

    while(i<curseur && id == id_evitement && itineraire_court[i][0] != -1 )//affiche l'itineraire
    {
        //PutsUART(UART_XBEE,"COUCOU ON BOUGE LA");
        if(last == rej && id == id_evitement)
        {
            rejoindre((double)(itineraire_court[i][0]*100)+50,(double)((itineraire_court[i][1])*100)+50,sens_marche,pourcentage_deplacement);
        }
        else
        {
            if(i == 1)
            {
                last = DEBUT_TRAJECTOIRE;
            }
            else
            {
                last = MILIEU_TRAJECTOIRE;
            }
            if(id == id_evitement)
            {
                passe_part((double)(itineraire_court[i+1][0]*100)+50,(double)((itineraire_court[i+1][1])*100)+50,sens_marche,pourcentage_deplacement,last);

            }
        }
        i++;
    }

    //if(i == curseur || i== curseur -1 || i == curseur +1){
         //PutsUART(UART_XBEE,"\n\ron a fait tout le chemin\n\r");
    //}

#endif
}

int distance()
{
    int i=0;
    int dist = 0;
    int addition;
    while(i <curseur && compteur_evitement < ATTENTE_EVITEMENT)
    {
        addition = itineraire[i][0] - itineraire[i+1][0];
        if(addition < 0)
            addition = addition * -1;
        dist = dist + addition;
        addition = itineraire[i][1] - itineraire[i+1][1];
        if(addition < 0)
            addition = addition * -1;
        dist = dist + addition;
        i++;
    }
    return dist;
}

void init_evitement()
{
    int i,j;

    //le 0;0 de la matrice correspond au 0;y_max du terrain

    id_evitement = 0;
    id_evitement_initial = 0;
    curseur_obstacle=0;
    precedent_obstacle[0]=-1;
    precedent_obstacle[1]=-1;
    precedent_obstacle[2]=-1;
    precedent_obstacle[3]=-1;

    for (j=0; j<y_max; j++) // initialisation de la carte et de ses contours
    {
        for(i=0; i<x_max; i++)
        {
#ifdef PETIT_ROBOT
            if(i<1 || i > x_max-2 || j<1 || j>y_max-2)
                obstacle[i][j]=1;
#endif

#ifdef GROS_ROBOT
            if(i<2 || i > x_max-3 || j<2 || j>y_max-3)
                obstacle[i][j]=1;
#endif
            else
                obstacle[i][j]=0;
        }
    }


    obstacle[2][18]=1;
    obstacle[3][18]=1;//petit palet
    obstacle[4][18]=1;
    obstacle[5][18]=1;
    obstacle[6][18]=1;//petit palet bis
    obstacle[7][18]=1;


    obstacle[22][18]=1;
    obstacle[27][18]=1;//petit palet
    obstacle[26][18]=1;
    obstacle[25][18]=1;
    obstacle[24][18]=1;//petit palet bis
    obstacle[23][18]=1;


#ifdef PETIT_ROBOT
    for(i=9; i<=20; i++) //escalier
    {
        for(j=12; j<=19; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif

#ifdef GROS_ROBOT

    for(i=9; i<=20; i++) //escalier
    {
        for(j=11; j<=19; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif

    for(i=10; i<=19; i++) // marche rose
    {
#ifdef PETIT_ROBOT
        for(j=0; j<=1; j++)
        {
            obstacle[i][j] =1;
        }
#endif
#ifdef GROS_ROBOT
        for(j=0; j<=2; j++)
        {
            obstacle[i][j] =1;
        }
#endif
    }


#ifdef PETIT_ROBOT
    for(i=0; i<=4; i++) //carre gauche haut
    {
        for(j=4; j<=7; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif
#ifdef GROS_ROBOT
    for(i=0; i<=5; i++) //carre gauche haut
    {
        for(j=4; j<=8; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif

#ifdef PETIT_ROBOT
    for(i=0; i<=4; i++) //carre gauche bas
    {
        for(j=12; j<=15; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif

#ifdef GROS_ROBOT

    for(i=0; i<=5; i++) //carre gauche bas
    {
        for(j=11; j<=15; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif

#ifdef PETIT_ROBOT
    for(i=23; i<=x_max; i++) //zone depart adverse
    {
        for(j=6; j<=13; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif
#ifdef GROS_ROBOT
    for(i=22; i<=x_max; i++) //zone depart adverse
    {
        for(j=5; j<=14; j++)
        {
            obstacle[i][j]=1;
        }
    }
#endif


}

int conversion_direction(int direction)//transforme la direction du blocage en une direction de longement
{
    switch (direction)
    {
    case 1://5 ou 7
        return 5;
        break;
    case 3://2 ou 4
        return 2;
        break;
    case 5://6 ou 8
        return 6;
        break;
    case 7://1 ou 3
        return 1;
        break;
    }
    return -1;
}

int longement ( int x_objectif,int y_objectif,int direction_longement) //longe un obstacle selon une direction de longement donn�e
{
    int nombre_point_parcouru=0;

    switch (direction_longement)
    {
    case 1 :
        while (y_actuel+1 <= y_max-1 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel][y_actuel+1] == 0 //tant que l'on peut descendre
                && obstacle [x_actuel-1][y_actuel] != 0 //et que la gauche de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            y_actuel = y_actuel+1; // on descend d'une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }

        if (obstacle [x_actuel-1][y_actuel] == 0 //si on peut aller a gauche, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 1; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=7;


                curseur = curseur +1;
                x_actuel=x_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point

            }
            return 0; // on a trouve un passage
        }
        else if((y_actuel == y_max-1 || obstacle [x_actuel][y_actuel+1] != 0) && obstacle [x_actuel+1][y_actuel] == 0)  //si on ne peut aller ni en bas ni a gauche mais a droite
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 1; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=3;


                curseur = curseur +1;
                x_actuel=x_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 5; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 2 :
        while (y_actuel+1 <= y_max-1 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel][y_actuel+1] == 0 //tant que l'on peut descendre
                && obstacle [x_actuel+1][y_actuel] != 0 //et que la droite de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            y_actuel = y_actuel+1; // on descend d'une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }


        if (obstacle [x_actuel+1][y_actuel] == 0 //si on peut aller a droite, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 1; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=3;

                curseur = curseur +1;
                x_actuel=x_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((y_actuel == y_max-1 ||obstacle [x_actuel][y_actuel+1] != 0 )&& obstacle [x_actuel-1][y_actuel] == 0)  //si on ne peut aller ni en haut ni a droite mais a gauche
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 1; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=7;

                curseur = curseur +1;
                x_actuel=x_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 7; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 3 :
        while (y_actuel -1 >=0 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel][y_actuel-1] == 0 //tant que l'on peut monter
                && obstacle [x_actuel-1][y_actuel] != 0 //et que la gauche de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            y_actuel = y_actuel-1; // on monte d'une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }


        if (obstacle [x_actuel-1][y_actuel] == 0 //si on peut aller a gauche, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 5; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=7;

                curseur = curseur +1;
                x_actuel=x_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((y_actuel == 0 || obstacle [x_actuel][y_actuel-1] != 0) && obstacle [x_actuel+1][y_actuel] == 0)  //si on ne peut aller ni en bas ni a gauche mais a droite
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 5; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=3;

                curseur = curseur +1;
                x_actuel=x_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 6; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en bas, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 4 :
        while (y_actuel -1 >=0 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel][y_actuel-1] == 0 //tant que l'on peut monter
                && obstacle [x_actuel+1][y_actuel] != 0 //et que la droite de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            y_actuel = y_actuel-1; // on monte d'une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }

        if (obstacle [x_actuel+1][y_actuel] == 0 //si on peut aller a droite, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 5; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=3;

                curseur = curseur +1;
                x_actuel=x_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((y_actuel == 0 || obstacle [x_actuel][y_actuel-1] != 0) && obstacle [x_actuel-1][y_actuel] == 0)  //si on ne peut aller ni en bas ni a droite mais a gauche
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 5; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=7;

                curseur = curseur +1;
                x_actuel=x_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 8; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en bas, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 5 :
        while (x_actuel +1 <=x_max-1 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel+1][y_actuel] == 0 //tant que l'on peut aller sur la droite
                && obstacle [x_actuel][y_actuel+1] != 0 //et que le bas de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            x_actuel = x_actuel+1; // on va sur la droite de une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }

        if (x_actuel == x_max)  // si on est en dehors de la matrice
        {

            return -1; // la recherche de passage de ce cote n'est pas fructueuse. peut �tre remplac�
        }

        else
        {
            if (obstacle [x_actuel][y_actuel+1] == 0 //si on peut aller en bas, si on a trouve un passage
                    || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
            {
                if(nombre_point_parcouru!=0)
                {
                    itineraire [curseur][2] = 3; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                    curseur = curseur +1;
                    itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                    itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                    itineraire [curseur][2]=1;

                    curseur = curseur +1;
                    y_actuel=y_actuel+1;
                    itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                    itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                }
                return 0; // on a trouve un passage
            }
            else if((x_actuel == x_max-1 || obstacle [x_actuel+1][y_actuel] != 0 )&& obstacle [x_actuel][y_actuel-1] == 0)  //si on ne peut aller ni en haut ni a droite mais en bas
            {
                if(nombre_point_parcouru!=0)
                {
                    itineraire [curseur][2] = 3; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                    curseur = curseur +1;
                    itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                    itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                    itineraire [curseur][2]=5;

                    curseur = curseur +1;
                    y_actuel=y_actuel-1;
                    itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                    itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                }
                return 4; // on renvoie la direction de longement a essayer

            }
            else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
            {
                return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
            }
        }
        break;


    case 6 :
        while (x_actuel +1 <=x_max-1 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel+1][y_actuel] == 0 //tant que l'on peut aller sur la droite
                && obstacle [x_actuel][y_actuel-1] != 0 //et que en haut de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            x_actuel = x_actuel+1; // on va sur la droite de une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }


        if (obstacle [x_actuel][y_actuel-1] == 0 //si on peut aller en haut, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 3; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=5;

                curseur = curseur +1;
                y_actuel=y_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((x_actuel == x_max -1 || obstacle [x_actuel+1][y_actuel] != 0 )&& obstacle [x_actuel][y_actuel+1] == 0)  //si on ne peut aller ni en bas ni a droite mais en haut
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 3; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=1;

                curseur = curseur +1;
                y_actuel=y_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 2; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 7 :
        while (x_actuel -1 >=0 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel-1][y_actuel] == 0 //tant que l'on peut aller sur la gauche
                && obstacle [x_actuel][y_actuel+1] != 0 //et que en bas de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            x_actuel = x_actuel-1; // on va sur la gauche de une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }


        if (obstacle [x_actuel][y_actuel+1] == 0 //si on peut aller en bas, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 7; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=1;

                curseur = curseur +1;
                y_actuel=y_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((x_actuel == 0 ||obstacle [x_actuel-1][y_actuel] != 0) && obstacle [x_actuel][y_actuel-1] == 0)  //si on ne peut aller ni en haut ni a gauche mais en bas
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 7; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=5;

                curseur = curseur +1;
                y_actuel=y_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 3; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;


    case 8 :
        while (x_actuel -1 >=0 //tant que l'on est toujours dans la matrice, que l'on est pas en dehors
                && obstacle [x_actuel-1][y_actuel] == 0 //tant que l'on peut aller sur la gauche
                && obstacle [x_actuel][y_actuel-1] != 0 //et que en haut de notre emplacement est condamnee
                && !(x_actuel == x_objectif && y_actuel == y_objectif)
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive (pas sur de l'utilite)
        {
            x_actuel = x_actuel-1; // on va sur la gauche de une case
            nombre_point_parcouru=nombre_point_parcouru+1;
        }


        if (obstacle [x_actuel][y_actuel-1] == 0 //si on peut aller en haut, si on a trouve un passage
                || (x_actuel == x_objectif && y_actuel == y_objectif) )  // ou que l'on est arrive(pas sur de l'utilite)
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 7; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=5;

                curseur = curseur +1;
                y_actuel=y_actuel-1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 0; // on a trouve un passage
        }
        else if((x_actuel == 0 || obstacle [x_actuel-1][y_actuel] != 0) && obstacle [x_actuel][y_actuel+1] == 0)  //si on ne peut aller ni en bas ni a gauche mais en haut
        {
            if(nombre_point_parcouru!=0)
            {
                itineraire [curseur][2] = 7; // pour aller de la derniere case enregistree a la case presente, on doit prendre cette direction

                curseur = curseur +1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
                itineraire [curseur][2]=1;

                curseur = curseur +1;
                y_actuel=y_actuel+1;
                itineraire [curseur][0] = x_actuel; //coordonnee en x du nouveau point
                itineraire [curseur][1] = y_actuel; //coordonnee en y du nouveau point
            }
            return 1; // on renvoie la direction de longement a essayer

        }
        else   // si on ne peut aller ni a gauche, ni en haut, ni a droite
        {
            return -1; //la recherche de passage de ce cote n'est pas fructueuse, on est dans un cul de sac
        }

        break;
    }
    return -1;
}

int tracer_ligne_x(int x_objectif) //cree une ligne droite suivant l'axe des x. Fais avancer ou reculer sur l'axe des x
{
    int nombre_point_parcouru=0;

    if(x_objectif>x_actuel)
    {
        while(x_actuel+1 <= x_max-1 //tant que l'on est dans la matrice
                && obstacle[x_actuel+1][y_actuel]==0 //tant que l'on peut aller a droite
                && x_objectif!=x_actuel
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive au niveau des x
        {
            x_actuel = x_actuel+1; // on va de 1 vers la droite
            nombre_point_parcouru=nombre_point_parcouru+1;
        }
        if(nombre_point_parcouru!=0)
        {
            itineraire[curseur][2]=3; // donne la direction pour aller de l'ancien point au nouveau point trouve
            curseur=curseur+1;
            itineraire[curseur][0]=x_actuel; //coordonnee en x du nouveau point
            itineraire[curseur][1]=y_actuel; //coordonnee en y du nouveau point
        }
        if(x_objectif==x_actuel)
        {
            return 0; //ok
        }
        else if(obstacle[x_actuel+1][y_actuel]!=0)
        {
            return 3; // retourne la direction du blocage
        }

    }
    else if (x_objectif<x_actuel)
    {
        while(x_actuel-1 >= 0 //tant que l'on est dans la matrice
                && obstacle[x_actuel-1][y_actuel]==0 //tant que l'on peut aller a gauche
                && x_objectif!=x_actuel
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive au niveau des x
        {
            x_actuel = x_actuel-1; // on va de 1 vers la gauche
            nombre_point_parcouru=nombre_point_parcouru+1;
        }
        if(nombre_point_parcouru!=0)
        {
            itineraire[curseur][2]=7; // donne la direction pour aller de l'ancien point au nouveau point trouve
            curseur=curseur+1;
            itineraire[curseur][0]=x_actuel; //coordonnee en x du nouveau point
            itineraire[curseur][1]=y_actuel; //coordonnee en y du nouveau point
        }

        if(x_objectif==x_actuel)
        {
            return 0; // pas de souci
        }
        else if(obstacle[x_actuel-1][y_actuel]!=0)
        {
            return 7;// retourne la direction du blocage
        }

    }
    return -1;
}

int tracer_ligne_y(int y_objectif) //cree une ligne droite suivant l'axe des y. Fais avancer ou reculer sur l'axe des y
{
    int nombre_point_parcouru=0;

    if(y_objectif>y_actuel)
    {
        while(y_actuel+1 <=y_max-1 //tant que l'on est dans la matrice
                && obstacle[x_actuel][y_actuel+1]==0 //tant que l'on peut aller en haut
                && y_objectif!=y_actuel
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive au niveau des y
        {
            y_actuel = y_actuel+1; // on va de 1 vers le haut
            nombre_point_parcouru=nombre_point_parcouru+1;
        }
        if(nombre_point_parcouru!=0)
        {
            itineraire[curseur][2]=1; // donne la direction pour aller de l'ancien point au nouveau point trouve
            curseur=curseur+1;
            itineraire[curseur][0]=x_actuel; //coordonnee en x du nouveau point
            itineraire[curseur][1]=y_actuel; //coordonnee en y du nouveau point
        }

        if(y_objectif==y_actuel)
        {
            return 0; // pas de souci
        }
        else if(obstacle[x_actuel][y_actuel+1]!=0)
        {
            return 1;// retourne la direction du blocage
        }

    }
    else if(y_objectif<y_actuel)
    {
        while(y_actuel-1 >= 0 //tant que l'on est dans la matrice
                && obstacle[x_actuel][y_actuel-1]==0 //tant que l'on peut aller en bas
                && y_objectif!=y_actuel
                && compteur_evitement < ATTENTE_EVITEMENT)  // et que l'on est pas arrive au niveau des y
        {
            y_actuel = y_actuel-1; // on va de 1 vers le bas
            nombre_point_parcouru=nombre_point_parcouru+1;
        }
        if(nombre_point_parcouru!=0)
        {
            itineraire[curseur][2]=5; // donne la direction pour aller de l'ancien point au nouveau point trouve
            curseur=curseur+1;
            itineraire[curseur][0]=x_actuel; //coordonnee en x du nouveau point
            itineraire[curseur][1]=y_actuel; //coordonnee en y du nouveau point
        }

        if(y_objectif==y_actuel)
        {
            return 0; // pas de souci
        }

        else if(obstacle[x_actuel][y_actuel-1]!=0)
        {
            return 5;// retourne la direction du blocage
        }

    }
    return -1;

}

void traitement_direction_identique()
{
    //post traitement 3) si deux directions consecutives sont les memes
    int i=0;
    int k=0;
    int flag;
    while(i<curseur && compteur_evitement < ATTENTE_EVITEMENT)
    {
        flag=0;//on a pu reduire le nombre de point de x points
        while (itineraire[i][2]==itineraire[i+1][2] && compteur_evitement < ATTENTE_EVITEMENT) //si deux directions consecutives ou plus
        {
            i++;
            flag++;
        }

        if(flag>0) // si on a eu le cas souhait�
        {
            //on d�cale les points
            for(k=i-flag+1; k<=curseur; k++)
            {
                itineraire[k][0]=itineraire[k+flag][0];
                itineraire[k][1]=itineraire[k+flag][1];
                itineraire[k][2]=itineraire[k+flag][2];

            }
            curseur=curseur-flag; //on r�duit le nombre de point
            i=i-flag;// et on se place au m�me point sur le nouvel itin�raire

            if(i<0) // si on est parti trop loin en arri�re
            {
                i=0; // on se remet au d�but
            }
        }
        i++;
    }
}

void traitement_deja_passe()
{
    int i,j,k;
    i=0;
    while(i<curseur+1 && compteur_evitement < ATTENTE_EVITEMENT) //s'occupe de quand on passe deux fois par le m�me point
    {
        j=curseur;

        //on part de la fin pour trouver la derni�re occurence de ce point s'il y en a une
        while(j>i && compteur_evitement < ATTENTE_EVITEMENT)
        {
            if(itineraire[i][0]==itineraire[j][0] && itineraire[i][1]==itineraire[j][1]) //si on a deux fois le m�me couple de coordonnees
            {
                for(k=i; k<=curseur; k++)//on se met a la premiere apparition et on place les points apr�s la seconde apparition
                {
                    itineraire[k][0]=itineraire[j+k-i][0];
                    itineraire[k][1]=itineraire[j+k-i][1];
                    itineraire[k][2]=itineraire[j+k-i][2];

                }
                curseur=curseur-(j-i);//on reduit le nombre de point pour rester coh�rent
                break;
            }
            j--;
        }
        i++;
    }
}

void traitement_escalier()
{
    int i=0;
    int j,k;
    int direction_1;
    int direction_2;

    while (i+1<curseur)
    {
        //si on a une diagonale qui fait un point de distance (+-1/+-1)
        if ((itineraire[i][0]-itineraire[i+2][0] == 1 || itineraire[i][0]-itineraire[i+2][0] == -1) && (itineraire[i][1]-itineraire[i+2][1] == 1 || itineraire[i][1]-itineraire[i+2][1] == -1))
        {
            j=i+2;
            // on sauvegarde les deux directions emprunt�es
            direction_1 = itineraire[i][2];
            if(i+1 <= curseur)
                direction_2 = itineraire[i+1][2];

            //si on a encore des points, que nous sommes dans les m�mes directions que pr�c�demment et que le d�placement est de 1 case verticale ou horizontale
            while (j+1<curseur && (itineraire[j][2] == direction_1 || itineraire [j][2] == direction_2)  && (((itineraire[j][0]-itineraire[j+1][0] == 1 || itineraire[j][0]-itineraire[j+1][0] == -1) && itineraire[j][1]-itineraire[j+1][1] == 0) || ((itineraire[j][1]-itineraire[j+1][1] == 1 || itineraire[j][1]-itineraire[j+1][1] == -1) && itineraire[j][0]-itineraire[j+1][0] == 0)))
            {
                j++; // on passe au point suivant
            }

            //cas sp�cifique pour les directions 1 et 7
            if((itineraire[i][2] == 1 && itineraire[i+1][2] == 7) || (itineraire[i][2] == 7 && itineraire[i+1][2] == 1))
                itineraire[i][2]=8;
            else
                itineraire[i][2] = direction_1 > direction_2 ? direction_1+1 : direction_2 +1; //en rajoutant 1 � la plus petite direction, on obtient la diagonale qui nous int�resse

            // on d�place les points qui n'ont pas �t� touch�s
            for(k=0; j+k<=curseur; k++)
            {
                itineraire[i+1+k][0]=itineraire[j+k][0];
                itineraire[i+1+k][1]=itineraire[j+k][1];
                itineraire[i+1+k][2]=itineraire[j+k][2];
            }
            // et on remet � jour le nombre de point
            curseur =curseur - j + i + 1;

        }
        i++;
    }

}

void post_traitement() //simplifie le trajet en elevant le maximum de deplacements inutiles
{
    int i;
    // on sauvegarde notre itineraire de base
    for(i=0; i<=curseur; i++)
    {
        itineraire_basique[i][0]=itineraire[i][0];
        itineraire_basique[i][1]=itineraire[i][1];
        itineraire_basique[i][2]=itineraire[i][2];
    }

    traitement_deja_passe();
    traitement_direction_identique();
    traitement_escalier();

}

int aiguillage_evitement(int x_objectif, int y_objectif, int direction,int haut)  // evitement par le haut ou par le bas
{
    int direction_longement;
    int cul_de_sac;
    int curseur_initial=curseur;
    int obstacle_initial = curseur_obstacle;
    int i;
    int test = 0;

    while(test <=1 && compteur_evitement < ATTENTE_EVITEMENT)
    {


        if(curseur_obstacle >= nb_point_max)
        {
            return -1;
        }

        curseur=curseur_initial;
        curseur_obstacle=obstacle_initial;
        if(haut==1)
        {
            direction_longement = conversion_direction(direction);//on passe de la direction du bloquage a la direction de longement
            cul_de_sac=0;
            while(direction_longement >0 && cul_de_sac == 0 && curseur < nb_point_max-1 && compteur_evitement < ATTENTE_EVITEMENT) //tant que l'on est bloque
            {

                direction_longement = longement(x_objectif,y_objectif,direction_longement);//on longe les obstacles
                for(i=0; i<curseur_initial; i++)
                {
                    if(i != curseur - 1 && itineraire[i][0] == itineraire[curseur-1][0] && itineraire[i][1] == itineraire[curseur-1][1] && itineraire[i][2] == itineraire[curseur-1][2] ) // on regarde si on est pas repasse par le meme point et la meme direction
                    {
                        cul_de_sac = -1;
                        if(chemin_court == 0)
                        {
                            haut =0;
                            test++;
                        }
                        else
                        {
                            test =2;
                        }
                    }

                }


            }
        }
        else if(direction_longement ==-1 || haut == 0) //si on a atteint un cul de sac ou on veut aller pour le haut
        {

            direction_longement = conversion_direction(direction);//on reprend la valeur de longement de depart
            if(direction_longement != -1)
                direction_longement=direction_longement+2; //on lui rajoute 1. Lors d'un blocage, on peut aller dans 2 directions. On tente ici la seconde direction
            cul_de_sac=0;
            while(direction_longement >0 && cul_de_sac == 0 && curseur < nb_point_max-1 && compteur_evitement < ATTENTE_EVITEMENT) //tant que l'on est bloque
            {
                direction_longement = longement(x_objectif,y_objectif,direction_longement);//on longe les obstacles
                for(i=0; i<curseur_initial; i++)
                {
                    if(i!= curseur -1 && itineraire[i][0] == itineraire[curseur-1][0] && itineraire[i][1] == itineraire[curseur-1][1] && itineraire[i][2] == itineraire[curseur-1][2] )// on regarde si on est pas repasse par le meme point et la meme direction
                    {
                        cul_de_sac = -1;
                        if(chemin_court == 0)
                        {
                            haut =1;
                            test++;
                        }
                        else
                        {
                            test =2;
                        }
                    }
                }
            }
        }
        if (direction_longement <=0)
            break;

    }
    if(test >=2 || direction_longement ==-1)
    {
        return -1;
    }
    else return direction_longement;

}

int evitement(int x_objectif,int y_objectif,int haut) //determine l'itineraire pour aller de notre position a l'objectif en tenant compte des obstacles eventuels
{
    int flag=1;// on essaye selon les x quand flag =1, selon les y si flag = 2
    int direction=0;
    int direction_longement=0;
    int i;

    while (flag > 0 && compteur_evitement < ATTENTE_EVITEMENT)// tant qu'il n'y a eu aucun probleme et qu'on a toujours le temps de calculer
    {

        if(curseur_obstacle >= nb_point_max) // si on a d�pass� le nombre d'obstacle maximale
        {
            return -1; // on arr�te
        }

        for(i=0; i<curseur-1; i++)
        {
            if(itineraire[i][0] == itineraire[curseur-1][0] && itineraire[i][1] == itineraire[curseur-1][1] && itineraire[i][2] == itineraire[curseur-1][2]) // si on tourne en rond
                return -1; // on arr�te
        }

        if(flag == 2 && y_actuel==y_objectif) // si on doit bouger sur les y et que notre coordonn�e en y correspond � celle de l'objectif
        {
            flag =1; // on bougera sur les x
        }

        if(flag == 1 && x_actuel==x_objectif) // si on doit bouger sur les x et que notre coordonn�e en x correspond � celle de l'objectif
        {
            flag =2; // on bougera sur les y
        }

        if(curseur >= nb_point_max-1) // si on a d�pass� le nombre de point d'itin�raire
        {
            return -1; // on arr�te
        }

        switch (flag)
        {
        case 1 :
            direction = tracer_ligne_x(x_objectif);//on trace une ligne droite et on voit si il y a bloquage
            if(direction != 0) //si l'on est bloque
            {

                //on sauvegarde notre obstacle
                point_obstacle[curseur_obstacle][0]=curseur;
                point_obstacle[curseur_obstacle][1]=direction;
                point_obstacle[curseur_obstacle][2]=haut;
                curseur_obstacle++;

                if(aiguillage_evitement(x_objectif,y_objectif,direction,haut) == -1) // Si notre tentative de longement ne fonctionne pas
                {
                    return -1; // on arr�te
                }
                //on ira ensuite repasser un nouveau tour du while(flag!=-1) pour continuer d'avancer sur les x
            }
            else if(x_actuel == x_objectif && y_actuel==y_objectif)//si on est arrive
                flag =0; // on a trouve un chemin et on sort
            else
            {
                flag = 2; // on essaye de bouger sur les y
            }
            break;

        case 2 :
            direction = tracer_ligne_y(y_objectif);//on trace une ligne droite et on voit si il y a bloquage
            if (direction != 0) //si blocage
            {
                //on sauvegarde notre obstacle
                point_obstacle[curseur_obstacle][0]=curseur;
                point_obstacle[curseur_obstacle][1]=direction;
                point_obstacle[curseur_obstacle][2]=haut;
                curseur_obstacle++;

                if(aiguillage_evitement(x_objectif,y_objectif,direction,haut) == -1)// Si notre tentative de longement ne fonctionne pas
                {
                    return -1;// on arr�te
                }

            }



            //on ira ensuite repasser un nouveau tour du while(flag!=-1) pour continuer d'avancer sur les y

            else if(x_actuel == x_objectif && y_actuel==y_objectif)//si on est arrive
                flag =0; // on a trouve un chemin et on sort
            else
            {
                flag = 1; // on essaye de bouger sur les x
            }
            break;
        }

        if(x_actuel == x_objectif && y_actuel==y_objectif)//si on est arrive
            flag =0; // on a trouve un chemin et on sort

        else if (direction_longement == -1) //si on est a un cul de sac
        {
            flag=-1;//on sort de cet itineraire
        }



    }

    if(flag==0) //si on est arrive
    {

        itineraire[curseur][2]=0;
        post_traitement();

        return 0; // on a trouve un chemin
    }
    else
    {
        return -1; // on a pas trouve de chemin
    }
}

void MAJ_obstacle(int x_present, int y_present,int angle,int8_t sens_marche,int action)
{
    int i,j;
    int ajout=1;
    int ajout_diago = 2;
#ifdef PETIT_ROBOT
    int taille = 1;// il y a deja 3 de largeur (devant nous, a cette gauche et a cette droite) la taille est ce qu'on met en plus de ces 3 la
    int taille_diago = 1;
    int vision = 2;
    int vision_diago = 1;
#endif
#ifdef GROS_ROBOT
    int taille = 1;// il y a deja 3 de largeur, devant nous, a cette gauche et a cette droite, la taille est ce qu'on met en plus de ces 3 la
    int taille_diago = 1;
    int vision = 2;
    int vision_diago = 1;
#endif

    int offset=0; // en fonction de si c'est le capteur gauche ou le droit ou la balise
    int largeur=0; // nombre de case recouverte PAR US (balise = 2us, le gauche et le droit) en plus des 3 cases en face de nous
    int x_obs,y_obs; // les coordonn�es d'un point de l'obstacle

    //les diff�rents groupes de d�tection en fonction de la localisation spatiale
    int droite = 0;
    int gauche = 0;
    int centre = 0;

    #ifdef GROS_ROBOT
    ajout = 2;
    ajout_diago = 2;
    #endif // GROS_ROBOT

    precedent_obstacle[0] = x_present;
    precedent_obstacle[1]= y_present;
    precedent_obstacle[2]= angle;
    precedent_obstacle[3] = sens_marche;

    if(EVITEMENT_ADV_ARRIERE == ON)
    {
        angle += 180;
    }
    if(angle < 0)
        angle = (int)(angle + 360) % 360;
    if(action == AJOUTER)
    {

#ifdef PETIT_ROBOT
    if((1 == CAPT_US_BALISE && EVITEMENT_ADV_AVANT == ON) || (1 == CAPT_IR_ARRIERE_CENTRE && EVITEMENT_ADV_ARRIERE == ON))
    {
        centre = 1;
    }
    if((1 == CAPT_US_DROIT && EVITEMENT_ADV_AVANT == ON) || (1 == CAPT_IR_ARRIERE_GAUCHE && EVITEMENT_ADV_ARRIERE == ON))
    {
        droite = 1;
    }
    if((1 == CAPT_US_GAUCHE && EVITEMENT_ADV_AVANT == ON) || (1 == CAPT_IR_ARRIERE_DROIT && EVITEMENT_ADV_ARRIERE == ON))
    {
        gauche = 1;
    }
#endif

#ifdef GROS_ROBOT
    if((1 == CAPT_US_BALISE && EVITEMENT_ADV_AVANT == ON) || (CAPT_US_ARRIERE == 1 && EVITEMENT_ADV_ARRIERE == ON))
    {
        centre = 1;
    }
    if(0 == CAPT_US_AV_GAUCHE && EVITEMENT_ADV_AVANT == ON)
    {
        gauche = 1;
    }
    if(0 == CAPT_US_AV_DROIT && EVITEMENT_ADV_AVANT == ON)
    {
        droite = 1;
    }
#endif
    }
    else
    {
        gauche = precedent_obstacle[4];
        centre = precedent_obstacle[5];
        droite = precedent_obstacle[6];
    }


    precedent_obstacle[4] = gauche;
    precedent_obstacle[5] = centre;
    precedent_obstacle[6] = droite;

    //ce qui suit correspond aux diff�rents cas de positionnement d'obstacle
    //on d�finit en premier les valeurs d'offset et de largeur avant d'appliquer l'obstacle
    //pour les obstacles en diagonale, on place un point d'obstacle plus 4 autres autour
    //de lui, en haut, en bas,� gauche et � droite. Pour lisser l'obstacle, certains de ces
    //points suppl�mentaires sont omis

    if(angle <= 22 || angle >= 339) //horizontale droite
    {
        if (centre == 1)
        {
            offset = - taille;
            largeur =taille*2;
        }
        else
        {

            if(droite == 1)
            {
                offset += -taille;
                largeur += taille;
            }

            if(gauche == 1)
            {
                offset += 0 ;
                largeur += taille;
            }
        }



        for(i=0; i<vision; i++)
        {
            for(j=-1 - ajout ; j<=largeur+1 + ajout; j++)
            {
                if(x_present+i+1 < x_max && y_present +offset +j >= 0 && y_present +offset +j < y_max && obstacle [x_present+i+1][y_present +offset + j] == 0)
                    obstacle [x_present+i+1][y_present +offset + j]=action;
            }
        }
    }


    else if(angle <=68 )
    {
        if(centre == 1)
        {
            largeur += 2*(taille_diago);
            offset += -taille_diago;
        }

        else
        {
            if(droite == 1)
            {
                largeur +=taille_diago;
                offset += -taille_diago;
            }


            if(gauche == 1)
            {
                largeur +=taille_diago;
                offset +=0;
            }
        }

        for(i=0; i<vision_diago; i++)
        {
            for(j=-ajout_diago; j<=largeur+ajout_diago; j++)
            {
                x_obs = x_present+1+offset+j+i;
                y_obs = y_present-1+offset+j-i;
                if(x_obs>=0 && x_obs < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs][y_obs] != 1)
                    obstacle[x_obs][y_obs] = action;
                if(!(j == largeur+ajout_diago)  && x_obs+1>=0 && x_obs+1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs+1][y_obs] != 1)
                    obstacle[x_obs+1][y_obs] = action;
                if(!(j == largeur+ajout_diago)&& x_obs>=0 && x_obs < x_max && y_obs+1 >=0 && y_obs+1 < y_max && obstacle [x_obs][y_obs+1] != 1)
                    obstacle[x_obs][y_obs+1] = action;
                if(!(j == -ajout_diago )  && x_obs-1>=0 && x_obs-1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs-1][y_obs] != 1)
                    obstacle[x_obs-1][y_obs] = action;
                if(!(j == -ajout_diago)  && x_obs>=0 && x_obs < x_max && y_obs-1 >=0 && y_obs-1 < y_max && obstacle [x_obs][y_obs-1] != 1)
                    obstacle[x_obs][y_obs-1] = action;
            }
        }
    }

    else if (angle <=112) //verticale en haut
    {
        if (centre == 1)
        {
            offset = - taille;
            largeur =taille*2;
        }

        else
        {
            if(droite)
            {
                offset += -taille;
                largeur += taille;
            }

            if(gauche)
            {
                offset += 0 ;
                largeur += taille;
            }

        }

        for(i=0; i<vision; i++)
        {
            for(j=-1-ajout; j<=largeur+1+ajout; j++)
            {
                if(y_present-i-1 >= 0 && x_present +offset + j>= 0 && x_present + offset + j < x_max && obstacle [x_present + offset + j][y_present-i-1] ==0)
                    obstacle [x_present + offset + j][y_present-i-1]=action;
            }
        }
    }


    else if(angle <=158 )
    {
        if(centre)
        {
            largeur += 2*taille_diago;
            offset += taille_diago;
        }

        else
        {

            if(gauche)
            {
                largeur +=taille_diago;
                offset += taille_diago;
            }


            if(droite)
            {
                largeur +=taille_diago;
                offset +=0;
            }
        }

        for(i=0; i<vision_diago; i++)
        {
            for(j=-ajout_diago; j<=largeur+ajout_diago; j++)
            {
                x_obs = x_present-1+offset-j-i;
                y_obs = y_present-1-offset+j-i;
                if(x_obs>=0 && x_obs < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs][y_obs] != 1)
                    obstacle[x_obs][y_obs] = action;
                if(!(j == -ajout_diago) && x_obs+1>=0 && x_obs+1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs+1][y_obs] != 1)
                    obstacle[x_obs+1][y_obs] = action;
                if(!(j == largeur+ajout_diago) && x_obs>=0 && x_obs < x_max && y_obs+1 >=0 && y_obs+1 < y_max && obstacle [x_obs][y_obs+1] != 1)
                    obstacle[x_obs][y_obs+1] = action;
                if(!(j == largeur+ajout_diago) && x_obs-1>=0 && x_obs-1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs-1][y_obs] != 1)
                    obstacle[x_obs-1][y_obs] = action;
                if(!(j == -ajout_diago) && x_obs>=0 && x_obs < x_max && y_obs-1 >=0 && y_obs-1 < y_max && obstacle [x_obs][y_obs-1] != 1)
                    obstacle[x_obs][y_obs-1] = action;
            }
        }
    }

    else if(angle <= 202) //horizontale gauche
    {


        if (centre)
        {
            offset = - taille;
            largeur =taille*2;
        }
        else
        {
            if(gauche)
            {
                offset += -taille;
                largeur += taille;
            }


            if(droite)
            {
                offset += 0 ;
                largeur += taille;
            }

        }
        for(i=0; i<vision; i++)
        {
            for(j=-1-ajout; j<=largeur+1+ajout; j++)
            {
                if(x_present-i-1 >=0 && y_present +offset + j >= 0 && y_present +offset + j < y_max && obstacle [x_present-i-1][y_present + offset + j]==0)
                    obstacle [x_present-i-1][y_present +offset + j]=action;
            }
        }
    }

    else if(angle <=248 )
    {
        if(centre)
        {
            largeur += 2*taille_diago;
            offset += taille_diago;
        }
        else
        {
            if(gauche)
            {
                largeur +=taille_diago;
                offset += taille_diago;
            }


            if(droite)
            {
                largeur +=taille_diago;
                offset +=0;
            }
        }
        for(i=0; i<vision_diago; i++)
        {
            for(j=-ajout_diago; j<=largeur+ajout_diago; j++)
            {
                x_obs = x_present-1-offset+j-i;
                y_obs = y_present+1-offset+j+i;
                if(x_obs>=0 && x_obs < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs][y_obs] != 1)
                obstacle[x_obs][y_obs] = action;
                if(!(j == largeur+ajout_diago ) && x_obs+1>=0 && x_obs+1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs+1][y_obs] != 1)
                    obstacle[x_obs+1][y_obs] = action;
                if(!(j == largeur+ajout_diago ) && x_obs>=0 && x_obs < x_max && y_obs+1 >=0 && y_obs+1 < y_max && obstacle [x_obs][y_obs+1] != 1)
                    obstacle[x_obs][y_obs+1] = action;
                if(!(j == -ajout_diago ) && x_obs-1>=0 && x_obs-1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs-1][y_obs] != 1)
                    obstacle[x_obs-1][y_obs] = action;
                if(!(j == -ajout_diago ) && x_obs>=0 && x_obs < x_max && y_obs-1 >=0 && y_obs-1 < y_max && obstacle [x_obs][y_obs-1] != 1)
                    obstacle[x_obs][y_obs-1] = action;
            }
        }
    }


    else   if(angle <=292 )// verticale en bas
    {

        if (centre)
        {
            offset = - taille;
            largeur =taille*2;
        }
        else
        {
            if(gauche)
            {
                offset += -taille;
                largeur += taille;
            }

            if(droite)
            {
                offset += 0 ;
                largeur += taille;
            }
        }
        for(i=0; i<vision; i++)
        {
            for(j=-1-ajout; j<=largeur+1+ajout; j++)
            {
                if(y_present+i+1 < y_max && x_present+ offset + j>= 0 && x_present + offset + j < x_max && obstacle [x_present + offset + j][y_present+i+1]==0)
                    obstacle [x_present + offset + j][y_present+i+1]=action;
            }
        }
    }

    else //if(angle <=338 )
    {
        if(centre)
        {
            largeur += 2*taille_diago;
            offset += taille_diago;
        }
        else
        {
            if(droite)
            {
                largeur +=taille_diago;
                offset += taille_diago;
            }


            if(gauche)
            {
                largeur +=taille_diago;
                offset +=0;
            }
        }
        for(i=0; i<vision_diago; i++)
        {
            for(j=-ajout_diago; j<=largeur+ajout_diago; j++)
            {
                x_obs = x_present+1+offset-j+i;
                y_obs = y_present+1-offset+j+i;
                if(x_obs>=0 && x_obs < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs][y_obs] != 1)
                    obstacle[x_obs][y_obs] = action;
                if(!(j == -ajout_diago ) && x_obs+1>=0 && x_obs+1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs+1][y_obs] != 1)
                    obstacle[x_obs+1][y_obs] = action;
                if(!(j == largeur+ajout_diago ) && x_obs>=0 && x_obs < x_max && y_obs+1 >=0 && y_obs+1 < y_max && obstacle [x_obs][y_obs+1] != 1)
                    obstacle[x_obs][y_obs+1] = action;
                if(!(j == largeur+ajout_diago )  && x_obs-1>=0 && x_obs-1 < x_max && y_obs >=0 && y_obs < y_max && obstacle [x_obs-1][y_obs] != 1)
                    obstacle[x_obs-1][y_obs] = action;
                if(!(j == -ajout_diago) && x_obs>=0 && x_obs < x_max && y_obs-1 >=0 && y_obs-1 < y_max && obstacle [x_obs][y_obs-1] != 1)
                    obstacle[x_obs][y_obs-1] = action;
            }
        }
    }
}
void deplacement_arriere(int8_t sens_marche)
{
    int i;
    int angle;
    if(sens_marche == MARCHE_AVANT) // si on est en marche avant, alors on reculera donc on multipliera -100 du avancer_reculer par 1 (i), et on change l'evitement
    {
        i=1;
        DETECTION = OFF;
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
        DETECTION = OFF;

    }
    else // si on est en marche arriere, alors on voudra avancer et non reculer, du coup on multpliera -100 par -1(i), et on change l'evitement
    {
        i=-1;

        DETECTION = OFF;
        EVITEMENT_ADV_ARRIERE = OFF;
        EVITEMENT_ADV_AVANT = ON;
        DETECTION = OFF;

    }

    angle= - get_orientation();
    if(angle < 0) // get_orientation renvoi des valeurs n�gatives donc on les repasse en positif
    {
        angle = (int)(angle + 360)%360;
    }

    //a partir de la, on va essayer de reculer si on peut ! les conditions qui suivent sont toutes les m�mes
    //si on est dans un certain angle, on check les 2 cases derrieres ou devant lui selon le sens de la marche
    //si elles sont libres, alors on peut reculer ou avancer
    //si on rentre en evitement dans ce reculer ou avancer, on se stoppera et on continuera la fonction d'evitement

#ifdef ORDI
    if(angle <= 22 || angle >= 339 ) //horizontale vers la droite
    {
        if(obstacle[x_actuel - i][y_actuel] == 0 && obstacle[x_actuel - 2*i][y_actuel] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }

    else if (angle <= 68) //diagonale en haut � droite
    {
        if( obstacle[x_actuel - i][y_actuel +1*i] == 0 && obstacle[x_actuel - 2*i][y_actuel +2*i] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }
    else if (angle <= 112) //verticale haut
    {
        if(obstacle[x_actuel][y_actuel +i] == 0 && obstacle[x_actuel][y_actuel +2*i] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }

    else if (angle <= 158) //diagonale en haut � gauche
    {
        if(obstacle[x_actuel +i][y_actuel +i] == 0 && obstacle[x_actuel + 2*i][y_actuel +2*i] == 0)
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }

    else if (angle <= 202) //horizontale gauche
    {
        if(obstacle[x_actuel +i][y_actuel] == 0 && obstacle[x_actuel + 2*i][y_actuel] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }
    else if (angle <= 248) //diagonale bas gauche

    {

        if(obstacle[x_actuel +i][y_actuel -i] == 0 && obstacle[x_actuel + 2*i][y_actuel -2*i] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }

    else if (angle <= 292) //verticale bas
    {
        if( obstacle[x_actuel][y_actuel -i] == 0 && obstacle[x_actuel][y_actuel -2*i] == 0 )
        {
            DETECTION = OFF;
            cout << "avancer_reculer("<<-100*i<<", 50)";
        }
    }

    else if (obstacle[x_actuel -i][y_actuel-i] == 0 && obstacle[x_actuel - 2*i][y_actuel-2*i] == 0 ) //diagonale bas droite
    {
        DETECTION = OFF;
        cout << "avancer_reculer("<<-100*i<<", 50)";
    }
#else

    if(angle <= 22 || angle >= 339 ) //horizontale vers la droite
    {
        if(obstacle[x_actuel - i][y_actuel] == 0 && obstacle[x_actuel - 2*i][y_actuel] == 0 )
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }

    else if (angle <= 68) //diagonale en haut � droite
    {
        if( obstacle[x_actuel - i][y_actuel +1*i] == 0 && obstacle[x_actuel - 2*i][y_actuel +2*i] == 0 )
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }
    else if (angle <= 112) //verticale haut
    {
        if(obstacle[x_actuel][y_actuel +i] == 0 && obstacle[x_actuel][y_actuel +2*i] == 0 )
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }

    else if (angle <= 158) //diagonale en haut � gauche
    {
        if(obstacle[x_actuel +i][y_actuel +i] == 0 && obstacle[x_actuel + 2*i][y_actuel +2*i] == 0)
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }

    else if (angle <= 202) //horizontale gauche
    {
        if(obstacle[x_actuel +i][y_actuel] == 0 && obstacle[x_actuel + 2*i][y_actuel] == 0 )
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }
    else if (angle <= 248) //diagonale bas gauche

    {
        if(obstacle[x_actuel +i][y_actuel -i] == 0 && obstacle[x_actuel + 2*i][y_actuel -2*i] == 0 )
        {
            //TIMER_DEBUG = ACTIVE;
            DETECTION = OFF;
            //TODO
            //A ENLEVER
            //i=-i;
            avancer_reculer((double)(-100*i), 50.);
        }

    }

    else if (angle <= 292) //verticale bas
    {
        if( obstacle[x_actuel][y_actuel -i] == 0 && obstacle[x_actuel][y_actuel -2*i] == 0 )
        {
            DETECTION = OFF;
            avancer_reculer((double)(-100*i), 50.);
        }
    }

    else if (obstacle[x_actuel -i][y_actuel-i] == 0 && obstacle[x_actuel - 2*i][y_actuel-2*i] == 0 ) //diagonale bas droite
    {
        DETECTION = OFF;
        avancer_reculer((double)(-100*i), 50.);
    }
#endif

    //on remet l'evitement comme il etait au d�part
    if(sens_marche == MARCHE_AVANT)
    {

        DETECTION = OFF;
        EVITEMENT_ADV_ARRIERE = OFF;
        EVITEMENT_ADV_AVANT = ON;
    }
    else
    {
        DETECTION = OFF;
        EVITEMENT_ADV_AVANT = OFF;
        EVITEMENT_ADV_ARRIERE = ON;
    }
}

void plus_court(int x_objectif,int y_objectif,int8_t sens_marche,double pourcentage_deplacement,char last,int ajout)
{
    int i,j;
    int retour=0;
    int curseur_finale;
    int curseur_obstacle_finale;
    int haut;
    int test_autre_sens=0;
    int sens_depart=1;
    int distance_courante;
    int nouvelle_distance;
    int id = id_evitement;
    id_evitement++;
    chemin_court=0;
    calcul_en_cours = ON;
    compteur_evitement = 0;

//     PutsUART(UART_XBEE, "\n\n\n\r X : ");
//    PutLongUART((int32_t) get_X());
//    PutcUART(UART_XBEE, '.');
//    PutcUART(UART_XBEE, ((uint8_t)((int32_t) ((double) get_X() * 10)) - (((int32_t) get_X()) * 10 )) +48);
//    PutsUART(UART_XBEE, " Y : ");
//    PutLongUART((int32_t) get_Y());
//    PutcUART(UART_XBEE, '.');
//    PutcUART(UART_XBEE, ((uint8_t)( (int32_t) ((double) (get_Y() * 10))) - (((int32_t) get_Y()) * 10 )) +48);
//    PutsUART(UART_XBEE, " Teta : ");
//    PutLongUART((int32_t) get_orientation());
//    PutcUART(UART_XBEE, '.');
//    PutcUART(UART_XBEE, ((uint8_t)( (int32_t) ((double) (get_orientation() * 10))) - (((int32_t) get_orientation()) * 10 )) +48);
//
//     PutsUART(UART_XBEE, "\n\r X Consigne : ");
//    PutLongUART((int32_t) x_objectif);
//    PutcUART(UART_XBEE, '.');
//    PutcUART(UART_XBEE, ((uint8_t)((int32_t) ((double) x_objectif * 10)) - (((int32_t) x_objectif) * 10 )) +48);
//    PutsUART(UART_XBEE, " Y Consigne : ");
//    PutLongUART((int32_t) y_objectif);
//    PutcUART(UART_XBEE, '.');
//    PutcUART(UART_XBEE, ((uint8_t)( (int32_t) ((double) (y_objectif * 10))) - (((int32_t) y_objectif) * 10 )) +48);
//    PutsUART(UART_XBEE, " Teta Consigne : ");


    if(pourcentage_deplacement > 50) // si la vitesse est sup�rieur � 50% de la vitesse maximale
    {
        pourcentage_deplacement = 50; // on la remet � 50% ce qui nous permet d'�viter les collisions � trop haute vitesse
    }

    if(id == id_evitement_initial) // si c'est le premier evitement lors de cette phase de deplacement
    {
        //on donne la cellule d'objectif
        x_obj = x_objectif/100;
        y_obj = y_objectif/100;
    }

    //on donne notre cellule de d�part
    x_actuel = get_X()/100;
    y_actuel = get_Y()/100;


    for(i=0; i<nb_point_max; i++) // on reset les diff�rents itineraires et les obstacles
    {
        itineraire[i][0]=-1;
        itineraire[i][1]=-1;
        itineraire[i][2]=-1;
        itineraire_basique[i][0]=-1;
        itineraire_basique[i][1]=-1;
        itineraire_basique[i][2]=-1;
        itineraire_court[i][0]=-1;
        itineraire_court[i][1]=-1;
        itineraire_court[i][2]=-1;
        point_obstacle[i][0]=-1;
        point_obstacle[i][1]=-1;
        point_obstacle[i][2]=-1;
    }
    curseur_obstacle = 0; ////on remet notre curseur de point d'obstacle au d�but

    // on efface le pr�c�dent obstacle mobile
    for(i=0; i<x_max; i++)
        for(j=0; j<y_max; j++)
            if(obstacle[i][j] == 2)
                obstacle[i][j] = 0;

    if(ajout == 1)
        MAJ_obstacle(x_actuel,y_actuel,- get_orientation(),sens_marche,AJOUTER); // on place notre nouvel obstacle

#ifdef DEBUG_HUGO
    PutsUART(UART_XBEE, "\n\r");
    PutIntUART(x_actuel);
    PutsUART(UART_XBEE, " ");
    PutIntUART(y_actuel);
    PutsUART(UART_XBEE, "||");
    PutIntUART(x_obj);
    PutsUART(UART_XBEE, " ");
    PutIntUART(y_obj);
    PutsUART(UART_XBEE, "\n\r");
    for(j=0; j<y_max; j++)
    {
        for(i=0; i+4<x_max; i=i+5)
        {
            PutIntUART(obstacle[i][j]*10000+obstacle[i+1][j]*1000+obstacle[i+2][j]*100+obstacle[i+3][j]*10+obstacle[i+4][j]);
        }
        PutsUART(UART_XBEE, "\n\r");
    }
#endif

#ifdef ORDI
    for(int j=y_max-1; j>=0; j--)
    {
        for(i=0; i<x_max; i++)
        {
            if(i==x_actuel && j==y_actuel)
                cout << "D";
            else if(i==x_obj && j==y_obj)
                cout << "A";
            else if(obstacle[i][j] !=0)
                cout << "X";
            else cout << "-";
        }
        cout << " "<<j<<endl;
    }
    for(i=0; i<x_max; i++)
    {
        cout << i%10;
    }
    cout <<endl;
#endif

    curseur =0;//on remet notre curseur de point itineraire au d�but

    //on place notre cellule actuelle comme point de d�part
    itineraire[curseur][0]=x_actuel;
    itineraire[curseur][1]=y_actuel;

    if(obstacle[x_obj][y_obj]!=0 || obstacle[x_actuel][y_actuel]!=0 || (x_actuel == x_obj && y_actuel == y_obj)) // si notre objectif est en obstacle, ou notre position, ou si on est dans la meme cellule que l'objectif
    {
        //alors on va reculer puis repartir vers l'objectif
        deplacement_arriere(sens_marche);
    }

    else // si notre cellule et celle de l'objectif sont libres
    {

        retour =evitement (x_obj,y_obj,sens_depart); // on essaye de trouver un chemin. On renvoi 0 si on a pu trouver un chemin, -1 sinon

        if(retour == 0) // si on a trouver un chemin
        {
            distance_courante = distance();// on calcul la distance entre notre de cellule travers�e

            //on stocke notre itineraire comme itineraire le plus court qu'on ait pour le moment (en m�me temps on en a pas d'autre)
            for(i=0; i<=curseur; i++)
            {
                itineraire_court[i][0] = itineraire[i][0];
                itineraire_court[i][1] = itineraire[i][1];
                itineraire_court[i][2] = itineraire[i][2];
            }

            // On stocke les diff�rentes valeurs qui caract�rise cet itineraire, comme le nombre de point et le nombre d'obstacle
            curseur_finale=curseur;
            curseur_obstacle_finale = curseur_obstacle;
            chemin_court=1;//on indique ici qu'on a au moins 1 chemin

        }
        else //sinon on va initialiser les valeurs que l'on peut
        {
            distance_courante=0;
            curseur_finale=curseur;
            curseur_obstacle_finale = curseur_obstacle;
            chemin_court =0;
            for(i=0; i<=curseur; i++)
            {
                itineraire_basique[i][0]=itineraire[i][0];
                itineraire_basique[i][1]=itineraire[i][1];
                itineraire_basique[i][2]=itineraire[i][2];
            }

        }

        //tant qu'on a pas re essaye a partir de tous nos obstacles et que le garde fou n'a pas ete declenche, on va chercher un chemin plus court
        while (curseur_obstacle> 0 && compteur_evitement < ATTENTE_EVITEMENT)
        {
            curseur=point_obstacle[curseur_obstacle-1][0];// on retourne au dernier obstacle qu'on a sauvegarde
            for(i=0; i<curseur; i++) // et on charge l'itineraire que l'on avait
            {
                itineraire[i][0]=itineraire_basique[i][0];
                itineraire[i][1]=itineraire_basique[i][1];
                itineraire[i][2]=itineraire_basique[i][2];
            }

            //on se replace comme il faut
            x_actuel = itineraire_basique[curseur][0];
            y_actuel = itineraire_basique[curseur][1];

            //et on se re inscrit sur l'itineraire
            itineraire[curseur][0]=x_actuel;
            itineraire[curseur][1]=y_actuel;


            haut = point_obstacle[curseur_obstacle-1][2];// on regarde si on est aller vers le haut ou vers le bas
            if(haut == 1)// si on passait par le haut
            {
                haut =0; // alors on passera par le bas
            }
            else // si on passait pas le bas
            {
                haut = 1;// alors on passera par le haut
            }

            retour=evitement(x_obj,y_obj,haut);//on retente de trouver un evitement


            if(curseur_obstacle >= nb_point_max)
            {
                break;
            }

            if(retour ==0)  // si on en a trouver un
            {
                chemin_court = 1;
                nouvelle_distance = distance(); //on recalcule le nombre de point
            }
            if(retour == 0 &&  (itineraire_court[0][0] == -1 || curseur < curseur_finale || nouvelle_distance < distance_courante))  // si on a un chemin valide soit on en avait pas soit plus court
            {

                for(i=0; i<curseur+1; i++) // on sauvegarde le nouvel itineraire
                {
                    itineraire_court[i][0] = itineraire[i][0];
                    itineraire_court[i][1] = itineraire[i][1];
                    itineraire_court[i][2] = itineraire[i][2];
                }

                // ainsi que les donn�es qui le caract�risent
                curseur_finale = curseur;
                distance_courante = nouvelle_distance;
                curseur_obstacle_finale = curseur_obstacle;
            }
            else    // si on a pas un chemin plus court
            {
                if(chemin_court ==1)
                    for(i=0; i<curseur_finale+1; i++) // on remet l'itineraire comme il �tait
                    {
                        itineraire[i][0] = itineraire_court[i][0];
                        itineraire[i][1] = itineraire_court[i][1];
                        itineraire[i][2] = itineraire_court[i][2];
                    }

                curseur_obstacle_finale = curseur_obstacle_finale-1; // et on recharge le curseur d'obstacle
            }
            curseur_obstacle = curseur_obstacle_finale;
            if(curseur_obstacle == 0 && test_autre_sens == 0) // si on a essaye tous les chemins d'un c�t� mais pas de l'autre
            {

                //alors on va essayer de l'autre c�t�
                test_autre_sens =1;
                for(i=0; i<nb_point_max; i++) // on reset les diff�rents itineraires et les obstacles
                {
                    point_obstacle[i][0]=-1;
                    point_obstacle[i][1]=-1;
                    point_obstacle[i][2]=-1;
                }
                curseur_obstacle = 0; ////on remet notre curseur de point d'obstacle au d�but
                curseur = 0;
                x_actuel = get_X()/100;
                y_actuel = get_Y()/100;

                itineraire[curseur][0]=x_actuel;
                itineraire[curseur][1]=y_actuel;

                retour =evitement (x_obj,y_obj,(sens_depart+1)%2); // on essaye de trouver un chemin. On renvoi 0 si on a pu trouver un chemin, -1 sinon

                if(retour ==0)  // si on en a trouver un
            {
                chemin_court = 1;
                nouvelle_distance = distance(); //on recalcule le nombre de point
            }
            if(retour == 0 &&  (itineraire_court[0][0] == -1 || curseur < curseur_finale || nouvelle_distance < distance_courante))  // si on a un chemin valide soit on en avait pas soit plus court
            {

                for(i=0; i<curseur+1; i++) // on sauvegarde le nouvel itineraire
                {
                    itineraire_court[i][0] = itineraire[i][0];
                    itineraire_court[i][1] = itineraire[i][1];
                    itineraire_court[i][2] = itineraire[i][2];
                }

                // ainsi que les donn�es qui le caract�risent
                curseur_finale = curseur;
                distance_courante = nouvelle_distance;
                curseur_obstacle_finale = curseur_obstacle;
            }
                else //sinon on va initialiser les valeurs que l'on peut
                {
                    curseur_obstacle_finale = curseur_obstacle;
                    for(i=0; i<=curseur; i++)
                    {
                        itineraire_basique[i][0]=itineraire[i][0];
                        itineraire_basique[i][1]=itineraire[i][1];
                        itineraire_basique[i][2]=itineraire[i][2];
                    }
                }
            }
        }


        if(chemin_court == 1) // si on a trouve un chemin
        {

        //PutsUART(UART_XBEE,"\n\ron a un chemin\n\r");
            curseur=curseur_finale; //on reprend notre curseur de l'itineraire le plus court
            deplacement(sens_marche,pourcentage_deplacement,last);// et on lance les deplacements
        }

        else // si on a pas trouve de chemin plus court
        {
            //alors on va reculer puis repartir vers l'objectif
            curseur = 0;
            deplacement_arriere(sens_marche);
        }
    }

    DETECTION = OFF;

    if(id_evitement-1 == id)
    {
        id_evitement_initial = id_evitement;

#ifdef ORDI
        //on redonne la consigne de base
        if(last == rej || last == FIN_TRAJECTOIRE)
        {
            cout << "rejoindre("<<x_objectif<<","<<y_objectif<<","<<sens_marche<<","<<pourcentage_deplacement<<")"<<endl;
        }
        else
        {
            cout <<"passe_part("<<x_objectif<<","<<y_objectif<<","<<sens_marche<<","<<pourcentage_deplacement<<","<<DEBUT_TRAJECTOIRE<<")"<<endl;
        }
#else
        //on redonne la consigne de base



        if(last == rej) // si nous utilisions un rejoindre
        {
             //PutsUART(UART_XBEE,"\n\ron renvoi l'ordre de rejoindre\n\r");
            rejoindre(x_objectif,y_objectif,sens_marche,pourcentage_deplacement);
        }
        else if (last == FIN_TRAJECTOIRE)// si on utilise un passe-part
        {


            if(chemin_court == 1 && curseur >1)// si on a eu un chemin avec des points interm�diaires
            {
                passe_part(x_objectif,y_objectif,sens_marche,pourcentage_deplacement,last);// on renvoi l'ordre initial
            }
            else
            {
                //PutsUART(UART_XBEE,"\n\ron renvoi l'ordre via fin trajectoire\n\r");
                rejoindre(x_objectif,y_objectif,sens_marche,pourcentage_deplacement); // sinon on envoi un rejoindre pour �viter les conflits de passe-part
            }
        }
        else
        {
            if(chemin_court == 1 && curseur > 1) //si on a un chemin et qu'il y'a au moins deux points dans le passe part
            {


                passe_part(x_objectif,y_objectif,sens_marche,pourcentage_deplacement,MILIEU_TRAJECTOIRE);

            }
            else
            {
                passe_part(x_objectif,y_objectif,sens_marche,pourcentage_deplacement,DEBUT_TRAJECTOIRE);
            }
        }
#endif
    }

    DETECTION = OFF;
    calcul_en_cours = OFF;
}

