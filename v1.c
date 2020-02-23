#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Lieu  {
	char nom [50] ;
	char desc [600] ;
	int diff;
	int id;
};



struct Ennemi  {
	char nom [50] ;
	char desc [600] ;
	int PV ;
};

struct Doute {
	char nom [50] ;
	char desc [600] ;
	int Moral ;
};

typedef struct Lieu lieu;
typedef struct Ennemi ennemi;
typedef struct Doute doute ;

int Persuasion (int Moral, int bGAMEOVER){
	int nAction = 5;
	int nSel = 0;
	int nCompteurHistoire =0 ;
	
	printf ("Vous avez cinq actions pour faire tomber le moral de votre cible a 0.\nVotre cible est un officier, dont le moral est de %d.\n", Moral);
	
	while (Moral>0 && nAction>0){
			printf ("Pour convaincre le garde, vous pouvez :\n(1) Le menacer\n(2) Tout lui raconter\n(3) L'inviter au restaurant.\n");
			scanf ("%d", &nSel);
			
			if(nSel == 1){
				//Effet menace.
				printf ("Vous menacez !\n(- Non mais dites donc, vous vous prenez pour qui, vous ?!)\n");
				printf ("Ca n'est pas efficace, a present, il n'a plus du tout envie de vous ecouter !\n");
				nAction = nAction-200;
			}
			
			else if (nSel == 2){
				//Effet histoire
				if (nCompteurHistoire == 0) {
					printf("Votre histoire ne l'impressionne pas, mais avec un peu plus de details, il acceptera sans doute de vous ecouter. Son moral baisse de cinq\n");
					nCompteurHistoire = nCompteurHistoire + 1 ;
					Moral = Moral - 5 ;
					nAction = nAction-1;
				}
				if (nCompteurHistoire == 1) {
					printf ("Vous vous engouffrez dans la faille et racontez tout ! Les details rajoutent de la veracite a votre recit, et il tombe d'accord avec vous !\n");
					Moral = Moral - 5 ;
					nAction = nAction-1;
				}
			}
			
			else if (nSel == 3){
				//Effet invitation
				printf ("Vous... Vous etes serieux, la ? Moi je disais ca pour rire, pour egailler un peu l'aventure...\n");
				nAction = nAction-1;
			}
			else{
				printf("Choisissez entre 1 et 3.\n");
				scanf ("%d", &nSel);
			}
	}
	if(Moral<=0){
		printf ("Vous assistez a un deploiement de force. En quelques heures, la planque ou vous etiez retenu est videe.\nFelicitations.\n");
	}
	if(nAction<0){
		printf ("On vous enferme le temps que vous repreniez vos esprits. Puis, le garde qui vous a enferme rentre chez lui avec la clef.\nC'etait son dernier jour de travail avant la retraite...\n");
		bGAMEOVER = 1;
	}
	return bGAMEOVER;
}

int Combat (int PV, int bGAMEOVER) {

	int i=0;
	//pvs du joueur et du monstre
	int nPVj = 40;
	int nPVm = PV;
	//sélecteurs d'attaque du joueur et du monstre
	int nSelJ= 0;
	int nSelM=0;
	//initiative, permet de savoir qui joue
	int nInit = 1;
	//indicateur de défense, activé par l'action "défense", désactivé après une attaque s'il est activé
	int nDefJ = 0;
	int nDefM=0;
	//nombre aléatoire entre int a et int b qui va servir de sélecteur au monstre.
	int a=1;
	int b=5;
	int rand_a_b(int a, int b){
		return rand()%(b-a) +a;
	}


		while(nPVj>0&&nPVm>0){
			
			//RAPPEL DES PVS ET PM
			printf("Vos points de vie : %d.\n", nPVj);
			for(i=0;i<nPVj;i++){
				printf("O");
			}
			printf("\n");
			printf("Les points de vie du garde : %d.\n", nPVm);
			for(i=0;i<nPVm;i++){
				printf("O");
			}
			printf("\n");
			
			printf("\nVous avez l'initiative.\n");
			
			//TOUR DU JOUEUR
			if(nInit=1){
							
				while(nInit==1){	
					printf("Voulez vous attaquer ? Saisissez : 1. Voulez vous vous defendre ? Saisissez 2.\n");
					scanf("%d",&nSelJ); 

					if(nSelJ!=1&&nSelJ!=2){
						printf("Choisissez entre 1 et 2.\n");
						scanf("%d",&nSelJ);
					}
					
					//ATTAQUE DU JOUEUR
					if(nSelJ==1){
						printf ("\n\nAttaque en cours !\n");
						
						//Si le monstre se défend
						if(nDefM==1){
							nPVm=nPVm-1;
							printf("Le monstre se defend, mais vous parvenez a le toucher !\nSes points de vie : %d. \n", nPVm);
							nDefM=0;
							nInit=0;
						}
						
						//Si le monstre ne se défend pas
						else{
							nPVm=nPVm-4;
							printf("Le monstre subit l'attaque de plein fouet.\nSes points de vie : %d. \n", nPVm);
							nInit=0;
						}
						
					}
					
					//DEFENSE DU JOUEUR
					if(nSelJ==2){
						printf("Vous vous defendez !\n");
						nDefJ=1;
						nInit=0;
					}
					
				}
			}
			printf("\n");
			
			//TOUR DU MONSTRE
			if(nInit==0){
								
				while(nInit==0){
					
					printf("Le monstre choisit son mouvement.\n");
					
					nSelM=rand_a_b(a, b);
					
					//ATTAQUE DU MONSTRE
					if(nSelM==1){
						printf("Le monstre attaque ! \n");
					
						//Si le joueur se défend
						if(nDefJ==1){
							nPVj=nPVj-1;
							printf("Vous vous defendez, mais perdez tout de meme de la vie !\nVos points de vie : %d. \n", nPVj);
							nDefJ=0;
							nInit=1;
						}
					
						//Si le joueur ne se défend pas
						else{
							nPVj=nPVj-4;
							printf("Vous subissez l'attaque de plein fouet.\nVos points de vie : %d. \n", nPVj);
							nInit=1;
						}
					}
					
					//DEFENSE DU MONSTRE
					if(nSelM==2){
						printf("Le monstre se defend !\n");
						nDefM=1;
						nInit=1;
					}
					
						
				}
			}
			printf("\n");
		}

		//FIN DE COMBAT

		if(nPVj<=0&&nPVm<=0){printf("Egalite !");}

		else{
			if(nPVj<=0){
				printf("GAME OVER");
				bGAMEOVER = 1;
			}
			
			if(nPVm<=0){
				printf("Vous avez gagne !");
			}
		}
		return bGAMEOVER;
}

int main (){
	//INTRODUCTION
	printf ("Vous avez ete transporte en Outre Monde. Apres un long periple a travers l'Ocean Atlantique, vous avez traverse le portail dans le triangle des Bermudes. \nArrive dans les eaux inconnues de l'Ocean Cisatinuque, vous avez fait cap au Sud et vous etes bientot arrives au Renevac.\nVous avez traverse la mer Interieure, et vous vous trouvez actuellement au port de Manrquins, la capitale.\n");
	int nLieuActuel = 0;
	int bGAMEOVER = 0;
	
	//PHASE 1 : LES TRAFIQUANTS
	//P1 : Intro
	printf ("\nVous etes immediatement repere par une agence de voyage, qui vous propose un tour du pays. Naivement, vous acceptez, et deux heures plus tard, vous vous retrouvez enchaine au fond d'une cave.\nGrace a la negligence des gardes, vous parvenez a vous liberer, mais l'un des gardes est toujours devant la porte.\nVous allez devoir vous en debarrasser.\n");
	ennemi Garde1 = {"Garde", "Un garde pataud.", 20};
	
	//P1 : Choix
	printf ("Voulez vous le provoquer pour attaquer (1) ou trouver un autre moyen de vous enfuir et vous faufiler dans son dos (2) ?\n");
	int nChoix = 0;
	scanf ("%d", &nChoix);
	
	//P1 : Combat 
	if(nChoix==1){
		bGAMEOVER = Combat (Garde1.PV, bGAMEOVER);
		if (bGAMEOVER!=1){
			printf ("Vous assommez le garde et fuyez.\n");
		}
	}
	
	//P1 : Infiltration
	else if(nChoix==2){
		printf("Vous decidez de ne pas provoquer le garde.\nEn observant les alentours, vous decouvrez qu'un precedent prisonnier a ecrit un message, que vous parvenez a lire.\n");
		printf("La porte s'ouvre avec un digicode ! Il est possible de l'atteindre dans le dos du garde. Le code est l'annee du couronnement d'Elizabeth II moins l'annee de la mort\ndu premier Empereur Romain !\n");
		printf ("Quel est le code a saisir ?\n");
		int nDigicode = 1925;
		int nDigicodeSaisi = 0;
		scanf("%d", &nDigicodeSaisi);
		if(nDigicodeSaisi == nDigicode){
			printf("Vous attendez la releve, ouvrez votre cellule et descendez des escaliers vers la lumiere de la rue.\n");
		}
		else{
			printf ("Un grand BIP BIP BIP retentit, et un garde accourt pour vous corriger directement dans votre cellule.\n");
			bGAMEOVER = Combat (Garde1.PV, bGAMEOVER);
			if (bGAMEOVER!=1){
				printf ("Vous assommez le garde et fuyez.\n");
			}
		}
	}
	else {
		while (nChoix!=1 && nChoix !=2){
			scanf ("Choisissez entre attaque (1) et discretion (2).%d", nChoix);
		}
	}
	
	printf("Vous etes parvenu a vous enfuir, et vous vous retrouvez dans une grande rue. Rapidement, vous retrouvez votre chemin. Vous allez directement au commissariat.\nL'officier ne croit pas ce que vous dites, convainquez-le !\n");
	doute officier1 = {"Officier", "Un officier de la Garde Grise.", 10};
	bGAMEOVER = Persuasion (officier1.Moral, bGAMEOVER);
	
	if(bGAMEOVER == 0){
		printf ("Felicitations ! Votre aide a ete precieuse pour arreter le trafic, et on vous promet le meilleur guide pour la suite de votre voyage !\n");
	}
	else if(bGAMEOVER == 1){
		printf ("Felicitations ! Vous avez gagne !... Ah, non, autant pour moi.\n");
	}
	
 return 0;
}