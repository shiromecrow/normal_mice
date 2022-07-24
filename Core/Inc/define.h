/*
 * define.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */

#ifndef INC_DEFINE_H_
#define INC_DEFINE_H_

#define ON 1
#define OFF 0
#define CONNECT 2

#define EXPLORATION 0
#define SHORTEST 1

#define LIPO_LIMIT 11.3

#define SPEAKER_LOUDNESS 0.005//

#define STEP_DEGREE 0.9//ステップ角[°]
#define TIRE_DIAMETER 50.9//タイヤ径[mm]
#define TREAD_WIDTH 82.12//トレッド幅[mm]

#define INTERRUPT_TIME 0.001//割り込み時間[s]

#define L_MOTOR_FRONT 0
#define L_MOTOR_BACK 1
#define R_MOTOR_FRONT 1
#define R_MOTOR_BACK 0

//　センサー名
#define SENSOR_FRONT_LEFT 0
#define SENSOR_FRONT_RIGHT 3
#define SENSOR_LEFT 1
#define SENSOR_RIGHT 2

//　指での最高センサー値
#define SENSOR_FINGER_0 400
#define SENSOR_FINGER_1 400
#define SENSOR_FINGER_2 400
#define SENSOR_FINGER_3 400

// 壁制御に使用する値
#define SENSOR_GAIN 0.09
#define CENTER_L 299
#define CENTER_R 327
#define CONTROLWALL_THRESHOLD_L 110//左壁制御の閾値
#define CONTROLWALL_THRESHOLD_R 110//右壁制御の閾値
#define CONTROLWALLCUT_THRESHOLD_L 25//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_R 25//右壁制御の壁切れの閾値

#define SENSOR_GAIN_SLANT 0.01
#define CONTROLWALL_THRESHOLD_FRONT_L 100//斜め用壁制御
#define CONTROLWALL_THRESHOLD_FRONT_R 150//斜め用壁制御


// 探索に使用する値
#define MAX_WALKCOUNT 255
#define GOAL_X 3
#define GOAL_Y 3
// 探索に使用する値(調整必要)
#define BACK_TO_CENTER 30.5//壁のケツ当てから中心までの距離
#define MAZE_OFFSET 20//迷路展開に使用するオフセット
#define F_PRESENCE 45
#define R_PRESENCE 100
#define L_PRESENCE 100


#endif /* INC_DEFINE_H_ */
