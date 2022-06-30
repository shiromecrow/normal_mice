/*
 * define.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */

#ifndef INC_DEFINE_H_
#define INC_DEFINE_H_

#define LIPO_LIMIT 11.3

#define SPEAKER_LOUDNESS 0.003//

#define STEP_DEGREE 0.9//ステップ角[°]
#define TIRE_DIAMETER 52//タイヤ径[mm]
#define TREAD_WIDTH 81//トレッド幅[mm]

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
#define SENSOR_GAIN 0.5
#define CENTER_L 120
#define CENTER_R 120
#define CONTROLWALL_THRESHOLD_L 80//左壁制御の閾値
#define CONTROLWALL_THRESHOLD_R 80//右壁制御の閾値
#define CONTROLWALLCUT_THRESHOLD_L 50//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_R 50//右壁制御の壁切れの閾値


#endif /* INC_DEFINE_H_ */
