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

speed700_shortest.SlalomCentervelocity=600;
speed700_shortest.TurnCentervelocity=700;


speed700_shortest.slalom_R.g_speed=speed700_shortest.SlalomCentervelocity;
speed700_shortest.slalom_R.t_speed=550;
speed700_shortest.slalom_R.t_acc=10000;
speed700_shortest.slalom_R.f_ofset=4;
speed700_shortest.slalom_R.e_ofset=12;

speed700_shortest.slalom_L.g_speed=speed700_shortest.SlalomCentervelocity;
speed700_shortest.slalom_L.t_speed=550;
speed700_shortest.slalom_L.t_acc=10000;
speed700_shortest.slalom_L.f_ofset=0;
speed700_shortest.slalom_L.e_ofset=15;

speed700_shortest.turn90_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn90_R.t_speed=430;
speed700_shortest.turn90_R.t_acc=10000;
speed700_shortest.turn90_R.f_ofset=63;
speed700_shortest.turn90_R.e_ofset=67;

speed700_shortest.turn90_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn90_L.t_speed=430;
speed700_shortest.turn90_L.t_acc=10000;
speed700_shortest.turn90_L.f_ofset=59;
speed700_shortest.turn90_L.e_ofset=70;

speed700_shortest.turn180_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn180_R.t_speed=480;
speed700_shortest.turn180_R.t_acc=10000;
speed700_shortest.turn180_R.f_ofset=60;
speed700_shortest.turn180_R.e_ofset=82;

speed700_shortest.turn180_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn180_L.t_speed=480;
speed700_shortest.turn180_L.t_acc=10000;
speed700_shortest.turn180_L.f_ofset=60;
speed700_shortest.turn180_L.e_ofset=80;

speed700_shortest.turn45in_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn45in_R.t_speed=450;
speed700_shortest.turn45in_R.t_acc=10000;
speed700_shortest.turn45in_R.f_ofset=28;
speed700_shortest.turn45in_R.e_ofset=70;

speed700_shortest.turn45in_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn45in_L.t_speed=450;
speed700_shortest.turn45in_L.t_acc=10000;
speed700_shortest.turn45in_L.f_ofset=27;
speed700_shortest.turn45in_L.e_ofset=68;

speed700_shortest.turn135in_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn135in_R.t_speed=500;
speed700_shortest.turn135in_R.t_acc=10000;
speed700_shortest.turn135in_R.f_ofset=36;
speed700_shortest.turn135in_R.e_ofset=57;

speed700_shortest.turn135in_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn135in_L.t_speed=500;
speed700_shortest.turn135in_L.t_acc=10000;
speed700_shortest.turn135in_L.f_ofset=37;
speed700_shortest.turn135in_L.e_ofset=37;

speed700_shortest.turn45out_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn45out_R.t_speed=450;
speed700_shortest.turn45out_R.t_acc=10000;
speed700_shortest.turn45out_R.f_ofset=42;
speed700_shortest.turn45out_R.e_ofset=12;

speed700_shortest.turn45out_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn45out_L.t_speed=450;
speed700_shortest.turn45out_L.t_acc=10000;
speed700_shortest.turn45out_L.f_ofset=40;
speed700_shortest.turn45out_L.e_ofset=10;

speed700_shortest.turn135out_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn135out_R.t_speed=500;
speed700_shortest.turn135out_R.t_acc=10000;
speed700_shortest.turn135out_R.f_ofset=25;
speed700_shortest.turn135out_R.e_ofset=90;

speed700_shortest.turn135out_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.turn135out_L.t_speed=500;
speed700_shortest.turn135out_L.t_acc=10000;
speed700_shortest.turn135out_L.f_ofset=40;
speed700_shortest.turn135out_L.e_ofset=95;

speed700_shortest.V90_R.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.V90_R.t_speed=550;
speed700_shortest.V90_R.t_acc=24500;
speed700_shortest.V90_R.f_ofset=50;
speed700_shortest.V90_R.e_ofset=65;

speed700_shortest.V90_L.g_speed=speed700_shortest.TurnCentervelocity;
speed700_shortest.V90_L.t_speed=550;
speed700_shortest.V90_L.t_acc=22000;
speed700_shortest.V90_L.f_ofset=28;
speed700_shortest.V90_L.e_ofset=55;


//*********************************900********************************************

speed900_shortest.SlalomCentervelocity=700;
speed900_shortest.TurnCentervelocity=900;


speed900_shortest.slalom_R.g_speed=speed900_shortest.SlalomCentervelocity;
speed900_shortest.slalom_R.t_speed=700;
speed900_shortest.slalom_R.t_acc=12000;
speed900_shortest.slalom_R.f_ofset=5;
speed900_shortest.slalom_R.e_ofset=5;

speed900_shortest.slalom_L.g_speed=speed900_shortest.SlalomCentervelocity;
speed900_shortest.slalom_L.t_speed=700;
speed900_shortest.slalom_L.t_acc=12000;
speed900_shortest.slalom_L.f_ofset=5;
speed900_shortest.slalom_L.e_ofset=5;

speed900_shortest.turn90_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn90_R.t_speed=500;
speed900_shortest.turn90_R.t_acc=10000;
speed900_shortest.turn90_R.f_ofset=48;
speed900_shortest.turn90_R.e_ofset=62;

speed900_shortest.turn90_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn90_L.t_speed=500;
speed900_shortest.turn90_L.t_acc=10000;
speed900_shortest.turn90_L.f_ofset=38;
speed900_shortest.turn90_L.e_ofset=60;

speed900_shortest.turn180_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn180_R.t_speed=550;
speed900_shortest.turn180_R.t_acc=10000;
speed900_shortest.turn180_R.f_ofset=40;
speed900_shortest.turn180_R.e_ofset=40;

speed900_shortest.turn180_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn180_L.t_speed=550;
speed900_shortest.turn180_L.t_acc=10000;
speed900_shortest.turn180_L.f_ofset=40;
speed900_shortest.turn180_L.e_ofset=40;

speed900_shortest.turn45in_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn45in_R.t_speed=500;
speed900_shortest.turn45in_R.t_acc=10000;
speed900_shortest.turn45in_R.f_ofset=25;
speed900_shortest.turn45in_R.e_ofset=60;

speed900_shortest.turn45in_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn45in_L.t_speed=500;
speed900_shortest.turn45in_L.t_acc=10000;
speed900_shortest.turn45in_L.f_ofset=32;
speed900_shortest.turn45in_L.e_ofset=60;

speed900_shortest.turn135in_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn135in_R.t_speed=500;
speed900_shortest.turn135in_R.t_acc=10000;
speed900_shortest.turn135in_R.f_ofset=53;
speed900_shortest.turn135in_R.e_ofset=47;

speed900_shortest.turn135in_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn135in_L.t_speed=500;
speed900_shortest.turn135in_L.t_acc=10000;
speed900_shortest.turn135in_L.f_ofset=40;
speed900_shortest.turn135in_L.e_ofset=55;

speed900_shortest.turn45out_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn45out_R.t_speed=500;
speed900_shortest.turn45out_R.t_acc=10000;
speed900_shortest.turn45out_R.f_ofset=45;
speed900_shortest.turn45out_R.e_ofset=10;

speed900_shortest.turn45out_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn45out_L.t_speed=500;
speed900_shortest.turn45out_L.t_acc=10000;
speed900_shortest.turn45out_L.f_ofset=40;
speed900_shortest.turn45out_L.e_ofset=10;

speed900_shortest.turn135out_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn135out_R.t_speed=500;
speed900_shortest.turn135out_R.t_acc=10000;
speed900_shortest.turn135out_R.f_ofset=25;
speed900_shortest.turn135out_R.e_ofset=90;

speed900_shortest.turn135out_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.turn135out_L.t_speed=500;
speed900_shortest.turn135out_L.t_acc=10000;
speed900_shortest.turn135out_L.f_ofset=40;
speed900_shortest.turn135out_L.e_ofset=95;

speed900_shortest.V90_R.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.V90_R.t_speed=550;
speed900_shortest.V90_R.t_acc=24500;
speed900_shortest.V90_R.f_ofset=50;
speed900_shortest.V90_R.e_ofset=65;

speed900_shortest.V90_L.g_speed=speed900_shortest.TurnCentervelocity;
speed900_shortest.V90_L.t_speed=550;
speed900_shortest.V90_L.t_acc=22000;
speed900_shortest.V90_L.f_ofset=28;
speed900_shortest.V90_L.e_ofset=55;

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
