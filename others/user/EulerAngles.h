/*******************************************************************************
// file				:	EulerAngles.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/

extern volatile float eu_yaw  , eu_pitch  , eu_roll  ;

void quaToEuler ( float w , float x , float y , float z );
