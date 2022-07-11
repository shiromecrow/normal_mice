/*
 * turning_parameter.c
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#include "turning_parameter.h"
#include "maze_Turning.h"


void input_parameter(void){

speed500_exploration.SlalomCentervelocity=500;
speed500_exploration.TurnCentervelocity=500;

speed500_exploration.slalom_R.g_speed=speed500_exploration.SlalomCentervelocity;
speed500_exploration.slalom_R.t_speed=550;
speed500_exploration.slalom_R.t_acc=10000;
speed500_exploration.slalom_R.f_ofset=4;//55;
speed500_exploration.slalom_R.e_ofset=25;

speed500_exploration.slalom_L.g_speed=speed500_exploration.SlalomCentervelocity;
speed500_exploration.slalom_L.t_speed=550;
speed500_exploration.slalom_L.t_acc=10000;
speed500_exploration.slalom_L.f_ofset=1;//50;
speed500_exploration.slalom_L.e_ofset=19;


speed500_exploration.turn90_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn90_R.t_speed=650;
speed500_exploration.turn90_R.t_acc=10000;
speed500_exploration.turn90_R.f_ofset=45;
speed500_exploration.turn90_R.e_ofset=46;

speed500_exploration.turn90_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn90_L.t_speed=650;
speed500_exploration.turn90_L.t_acc=10000;
speed500_exploration.turn90_L.f_ofset=50;
speed500_exploration.turn90_L.e_ofset=47;

speed500_exploration.turn180_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn180_R.t_speed=800;
speed500_exploration.turn180_R.t_acc=8000;
speed500_exploration.turn180_R.f_ofset=20;
speed500_exploration.turn180_R.e_ofset=30;

speed500_exploration.turn180_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn180_L.t_speed=780;
speed500_exploration.turn180_L.t_acc=8000;
speed500_exploration.turn180_L.f_ofset=20;
speed500_exploration.turn180_L.e_ofset=40;

speed500_exploration.turn45in_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn45in_R.t_speed=900;
speed500_exploration.turn45in_R.t_acc=13000;
speed500_exploration.turn45in_R.f_ofset=25;
speed500_exploration.turn45in_R.e_ofset=60;

speed500_exploration.turn45in_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn45in_L.t_speed=900;
speed500_exploration.turn45in_L.t_acc=13000;
speed500_exploration.turn45in_L.f_ofset=32;
speed500_exploration.turn45in_L.e_ofset=60;

speed500_exploration.turn135in_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn135in_R.t_speed=900;
speed500_exploration.turn135in_R.t_acc=12000;
speed500_exploration.turn135in_R.f_ofset=53;
speed500_exploration.turn135in_R.e_ofset=47;

speed500_exploration.turn135in_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn135in_L.t_speed=900;
speed500_exploration.turn135in_L.t_acc=12000;
speed500_exploration.turn135in_L.f_ofset=40;
speed500_exploration.turn135in_L.e_ofset=55;

speed500_exploration.turn45out_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn45out_R.t_speed=900;
speed500_exploration.turn45out_R.t_acc=10000;
speed500_exploration.turn45out_R.f_ofset=45;
speed500_exploration.turn45out_R.e_ofset=10;

speed500_exploration.turn45out_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn45out_L.t_speed=900;
speed500_exploration.turn45out_L.t_acc=10000;
speed500_exploration.turn45out_L.f_ofset=40;
speed500_exploration.turn45out_L.e_ofset=10;

speed500_exploration.turn135out_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn135out_R.t_speed=1000;
speed500_exploration.turn135out_R.t_acc=12000;
speed500_exploration.turn135out_R.f_ofset=25;
speed500_exploration.turn135out_R.e_ofset=90;

speed500_exploration.turn135out_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.turn135out_L.t_speed=1000;
speed500_exploration.turn135out_L.t_acc=12000;
speed500_exploration.turn135out_L.f_ofset=40;
speed500_exploration.turn135out_L.e_ofset=95;

speed500_exploration.V90_R.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.V90_R.t_speed=1650;
speed500_exploration.V90_R.t_acc=24500;
speed500_exploration.V90_R.f_ofset=50;
speed500_exploration.V90_R.e_ofset=65;

speed500_exploration.V90_L.g_speed=speed500_exploration.TurnCentervelocity;
speed500_exploration.V90_L.t_speed=1550;
speed500_exploration.V90_L.t_acc=22000;
speed500_exploration.V90_L.f_ofset=28;
speed500_exploration.V90_L.e_ofset=55;



//*********************************600********************************************

speed600_shortest.SlalomCentervelocity=500;
speed600_shortest.TurnCentervelocity=600;


speed600_shortest.slalom_R.g_speed=speed600_shortest.SlalomCentervelocity;
speed600_shortest.slalom_R.t_speed=650;
speed600_shortest.slalom_R.t_acc=15000;
speed600_shortest.slalom_R.f_ofset=47;
speed600_shortest.slalom_R.e_ofset=40;

speed600_shortest.slalom_L.g_speed=speed600_shortest.SlalomCentervelocity;
speed600_shortest.slalom_L.t_speed=650;
speed600_shortest.slalom_L.t_acc=15000;
speed600_shortest.slalom_L.f_ofset=53;
speed600_shortest.slalom_L.e_ofset=44;

speed600_shortest.turn90_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn90_R.t_speed=650;
speed600_shortest.turn90_R.t_acc=10000;
speed600_shortest.turn90_R.f_ofset=45;
speed600_shortest.turn90_R.e_ofset=46;

speed600_shortest.turn90_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn90_L.t_speed=650;
speed600_shortest.turn90_L.t_acc=10000;
speed600_shortest.turn90_L.f_ofset=50;
speed600_shortest.turn90_L.e_ofset=47;

speed600_shortest.turn180_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn180_R.t_speed=800;
speed600_shortest.turn180_R.t_acc=8000;
speed600_shortest.turn180_R.f_ofset=20;
speed600_shortest.turn180_R.e_ofset=30;

speed600_shortest.turn180_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn180_L.t_speed=780;
speed600_shortest.turn180_L.t_acc=8000;
speed600_shortest.turn180_L.f_ofset=20;
speed600_shortest.turn180_L.e_ofset=40;

speed600_shortest.turn45in_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn45in_R.t_speed=900;
speed600_shortest.turn45in_R.t_acc=13000;
speed600_shortest.turn45in_R.f_ofset=25;
speed600_shortest.turn45in_R.e_ofset=60;

speed600_shortest.turn45in_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn45in_L.t_speed=900;
speed600_shortest.turn45in_L.t_acc=13000;
speed600_shortest.turn45in_L.f_ofset=32;
speed600_shortest.turn45in_L.e_ofset=60;

speed600_shortest.turn135in_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn135in_R.t_speed=900;
speed600_shortest.turn135in_R.t_acc=12000;
speed600_shortest.turn135in_R.f_ofset=53;
speed600_shortest.turn135in_R.e_ofset=47;

speed600_shortest.turn135in_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn135in_L.t_speed=900;
speed600_shortest.turn135in_L.t_acc=12000;
speed600_shortest.turn135in_L.f_ofset=40;
speed600_shortest.turn135in_L.e_ofset=55;

speed600_shortest.turn45out_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn45out_R.t_speed=900;
speed600_shortest.turn45out_R.t_acc=10000;
speed600_shortest.turn45out_R.f_ofset=45;
speed600_shortest.turn45out_R.e_ofset=10;

speed600_shortest.turn45out_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn45out_L.t_speed=900;
speed600_shortest.turn45out_L.t_acc=10000;
speed600_shortest.turn45out_L.f_ofset=40;
speed600_shortest.turn45out_L.e_ofset=10;

speed600_shortest.turn135out_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn135out_R.t_speed=1000;
speed600_shortest.turn135out_R.t_acc=12000;
speed600_shortest.turn135out_R.f_ofset=25;
speed600_shortest.turn135out_R.e_ofset=90;

speed600_shortest.turn135out_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.turn135out_L.t_speed=1000;
speed600_shortest.turn135out_L.t_acc=12000;
speed600_shortest.turn135out_L.f_ofset=40;
speed600_shortest.turn135out_L.e_ofset=95;

speed600_shortest.V90_R.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.V90_R.t_speed=1650;
speed600_shortest.V90_R.t_acc=24500;
speed600_shortest.V90_R.f_ofset=50;
speed600_shortest.V90_R.e_ofset=65;

speed600_shortest.V90_L.g_speed=speed600_shortest.TurnCentervelocity;
speed600_shortest.V90_L.t_speed=1550;
speed600_shortest.V90_L.t_acc=22000;
speed600_shortest.V90_L.f_ofset=28;
speed600_shortest.V90_L.e_ofset=55;


//*********************************800********************************************

speed600_shortest.SlalomCentervelocity=600;
speed600_shortest.TurnCentervelocity=800;


speed800_shortest.slalom_R.g_speed=1000;
speed800_shortest.slalom_R.t_speed=1000;
speed800_shortest.slalom_R.t_acc=14000;
speed800_shortest.slalom_R.f_ofset=0;
speed800_shortest.slalom_R.e_ofset=15;

speed800_shortest.slalom_L.g_speed=1000;
speed800_shortest.slalom_L.t_speed=1000;
speed800_shortest.slalom_L.t_acc=14000;
speed800_shortest.slalom_L.f_ofset=5;
speed800_shortest.slalom_L.e_ofset=5;

speed800_shortest.turn90_R.g_speed=500;
speed800_shortest.turn90_R.t_speed=650;
speed800_shortest.turn90_R.t_acc=15000;
speed800_shortest.turn90_R.f_ofset=55;
speed800_shortest.turn90_R.e_ofset=40;

speed800_shortest.turn90_L.g_speed=500;
speed800_shortest.turn90_L.t_speed=650;
speed800_shortest.turn90_L.t_acc=15000;
speed800_shortest.turn90_L.f_ofset=50;
speed800_shortest.turn90_L.e_ofset=44;

speed800_shortest.turn180_R.g_speed=500;
speed800_shortest.turn180_R.t_speed=650;
speed800_shortest.turn180_R.t_acc=15000;
speed800_shortest.turn180_R.f_ofset=55;
speed800_shortest.turn180_R.e_ofset=40;

speed800_shortest.turn180_L.g_speed=500;
speed800_shortest.turn180_L.t_speed=650;
speed800_shortest.turn180_L.t_acc=15000;
speed800_shortest.turn180_L.f_ofset=50;
speed800_shortest.turn180_L.e_ofset=44;

speed800_shortest.turn45in_R.g_speed=500;
speed800_shortest.turn45in_R.t_speed=650;
speed800_shortest.turn45in_R.t_acc=15000;
speed800_shortest.turn45in_R.f_ofset=55;
speed800_shortest.turn45in_R.e_ofset=40;

speed800_shortest.turn45in_L.g_speed=500;
speed800_shortest.turn45in_L.t_speed=650;
speed800_shortest.turn45in_L.t_acc=15000;
speed800_shortest.turn45in_L.f_ofset=50;
speed800_shortest.turn45in_L.e_ofset=44;

speed800_shortest.turn135in_R.g_speed=500;
speed800_shortest.turn135in_R.t_speed=650;
speed800_shortest.turn135in_R.t_acc=15000;
speed800_shortest.turn135in_R.f_ofset=55;
speed800_shortest.turn135in_R.e_ofset=40;

speed800_shortest.turn135in_L.g_speed=500;
speed800_shortest.turn135in_L.t_speed=650;
speed800_shortest.turn135in_L.t_acc=15000;
speed800_shortest.turn135in_L.f_ofset=50;
speed800_shortest.turn135in_L.e_ofset=44;

speed800_shortest.turn45out_R.g_speed=500;
speed800_shortest.turn45out_R.t_speed=650;
speed800_shortest.turn45out_R.t_acc=15000;
speed800_shortest.turn45out_R.f_ofset=55;
speed800_shortest.turn45out_R.e_ofset=40;

speed800_shortest.turn45out_L.g_speed=500;
speed800_shortest.turn45out_L.t_speed=650;
speed800_shortest.turn45out_L.t_acc=15000;
speed800_shortest.turn45out_L.f_ofset=50;
speed800_shortest.turn45out_L.e_ofset=44;

speed800_shortest.turn135out_R.g_speed=500;
speed800_shortest.turn135out_R.t_speed=650;
speed800_shortest.turn135out_R.t_acc=15000;
speed800_shortest.turn135out_R.f_ofset=55;
speed800_shortest.turn135out_R.e_ofset=40;

speed800_shortest.turn135out_L.g_speed=500;
speed800_shortest.turn135out_L.t_speed=650;
speed800_shortest.turn135out_L.t_acc=15000;
speed800_shortest.turn135out_L.f_ofset=50;
speed800_shortest.turn135out_L.e_ofset=44;

speed800_shortest.V90_R.g_speed=500;
speed800_shortest.V90_R.t_speed=650;
speed800_shortest.V90_R.t_acc=15000;
speed800_shortest.V90_R.f_ofset=55;
speed800_shortest.V90_R.e_ofset=40;

speed800_shortest.V90_L.g_speed=500;
speed800_shortest.V90_L.t_speed=650;
speed800_shortest.V90_L.t_acc=15000;
speed800_shortest.V90_L.f_ofset=50;
speed800_shortest.V90_L.e_ofset=44;

//*********************************1000********************************************

speed1000_shortest.slalom_R.g_speed=1000;
speed1000_shortest.slalom_R.t_speed=550;
speed1000_shortest.slalom_R.t_acc=12000;
speed1000_shortest.slalom_R.f_ofset=30;
speed1000_shortest.slalom_R.e_ofset=60;

speed1000_shortest.slalom_L.g_speed=1000;
speed1000_shortest.slalom_L.t_speed=550;
speed1000_shortest.slalom_L.t_acc=12000;
speed1000_shortest.slalom_L.f_ofset=30;
speed1000_shortest.slalom_L.e_ofset=60;

speed1000_shortest.turn90_R.g_speed=1000;
speed1000_shortest.turn90_R.t_speed=400;
speed1000_shortest.turn90_R.t_acc=12000;
speed1000_shortest.turn90_R.f_ofset=30;
speed1000_shortest.turn90_R.e_ofset=60;

speed1000_shortest.turn90_L.g_speed=1000;
speed1000_shortest.turn90_L.t_speed=400;
speed1000_shortest.turn90_L.t_acc=12000;
speed1000_shortest.turn90_L.f_ofset=30;
speed1000_shortest.turn90_L.e_ofset=60;

speed1000_shortest.turn180_R.g_speed=1000;
speed1000_shortest.turn180_R.t_speed=500;
speed1000_shortest.turn180_R.t_acc=10000;
speed1000_shortest.turn180_R.f_ofset=30;
speed1000_shortest.turn180_R.e_ofset=70;

speed1000_shortest.turn180_L.g_speed=1000;
speed1000_shortest.turn180_L.t_speed=500;
speed1000_shortest.turn180_L.t_acc=10000;
speed1000_shortest.turn180_L.f_ofset=30;
speed1000_shortest.turn180_L.e_ofset=70;

speed1000_shortest.turn45in_R.g_speed=1000;
speed1000_shortest.turn45in_R.t_speed=750;
speed1000_shortest.turn45in_R.t_acc=12000;
speed1000_shortest.turn45in_R.f_ofset=20;
speed1000_shortest.turn45in_R.e_ofset=70;

speed1000_shortest.turn45in_L.g_speed=1000;
speed1000_shortest.turn45in_L.t_speed=750;
speed1000_shortest.turn45in_L.t_acc=12000;
speed1000_shortest.turn45in_L.f_ofset=20;
speed1000_shortest.turn45in_L.e_ofset=70;

speed1000_shortest.turn135in_R.g_speed=1000;
speed1000_shortest.turn135in_R.t_speed=680;
speed1000_shortest.turn135in_R.t_acc=14000;
speed1000_shortest.turn135in_R.f_ofset=20;
speed1000_shortest.turn135in_R.e_ofset=50;

speed1000_shortest.turn135in_L.g_speed=1000;
speed1000_shortest.turn135in_L.t_speed=680;
speed1000_shortest.turn135in_L.t_acc=14000;
speed1000_shortest.turn135in_L.f_ofset=20;
speed1000_shortest.turn135in_L.e_ofset=50;

speed1000_shortest.turn45out_R.g_speed=1000;
speed1000_shortest.turn45out_R.t_speed=750;
speed1000_shortest.turn45out_R.t_acc=14000;
speed1000_shortest.turn45out_R.f_ofset=50;
speed1000_shortest.turn45out_R.e_ofset=50;

speed1000_shortest.turn45out_L.g_speed=1000;
speed1000_shortest.turn45out_L.t_speed=750;
speed1000_shortest.turn45out_L.t_acc=14000;
speed1000_shortest.turn45out_L.f_ofset=50;
speed1000_shortest.turn45out_L.e_ofset=50;

speed1000_shortest.turn135out_R.g_speed=1000;
speed1000_shortest.turn135out_R.t_speed=770;
speed1000_shortest.turn135out_R.t_acc=14000;
speed1000_shortest.turn135out_R.f_ofset=30;
speed1000_shortest.turn135out_R.e_ofset=90;

speed1000_shortest.turn135out_L.g_speed=1000;
speed1000_shortest.turn135out_L.t_speed=770;
speed1000_shortest.turn135out_L.t_acc=14000;
speed1000_shortest.turn135out_L.f_ofset=30;
speed1000_shortest.turn135out_L.e_ofset=90;

speed1000_shortest.V90_R.g_speed=1000;
speed1000_shortest.V90_R.t_speed=950;
speed1000_shortest.V90_R.t_acc=18000;
speed1000_shortest.V90_R.f_ofset=20;
speed1000_shortest.V90_R.e_ofset=60;

speed1000_shortest.V90_L.g_speed=1000;
speed1000_shortest.V90_L.t_speed=950;
speed1000_shortest.V90_L.t_acc=18000;
speed1000_shortest.V90_L.f_ofset=20;
speed1000_shortest.V90_L.e_ofset=60;




}
