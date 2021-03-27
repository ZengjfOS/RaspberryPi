#!/bin/bash

PWM_BASE_PATH=/sys/class/pwm/pwmchip0
PWM_NUM=0
PERIOD_DEFAULT_VALUE=10000
CURRENT_DUTY_CYCLE_DIV=50

function help() {
	echo
	echo "help:"
	echo "    fanhat [duty for %]"
	echo "    example:"
	echo "        1. fanhat 50"
	echo "        2. fanhat 80"
	echo "    detail info:"
	echo "        1. period is $PERIOD_DEFAULT_VALUE in ns"
	echo "        2. duty range: 0 ~ 100"
}

if [ $# -eq 0 ]; then
	CURRENT_DUTY_CYCLE_DIV=50
elif [ $# -gt 0 ]; then
	if [[ $1 =~ ^[0-9]+$ ]]; then
		CURRENT_DUTY_CYCLE_DIV=$1
	else
		echo "[info] duty value [$1] is not digits/numerical characters"
		help
		exit 1
	fi

	if [ $1 -gt 100 ]; then
		echo "[info] duty value [$1] out of range 0 ~ 100"
		help
		exit 1
	fi
fi

if [ ! -d "${PWM_BASE_PATH}/pwm${PWM_NUM}" ];then
	echo ${PWM_NUM} > ${PWM_BASE_PATH}/export

	sleep 1
	if [ ! -d "${PWM_BASE_PATH}/pwm${PWM_NUM}" ];then
		echo "[info] export pwm${PWM_NUM} failed, check it again."
		exit 1
	fi

	# 如果你手动unexport的情况下，复位enable是必须的
	echo 0 > ${PWM_BASE_PATH}/pwm${PWM_NUM}/enable

	echo "export pwm${PWM_NUM} success"
fi

CURRENT_DUTY_CYCLE=$((PERIOD_DEFAULT_VALUE / 100 * ${CURRENT_DUTY_CYCLE_DIV}))

cd "${PWM_BASE_PATH}/pwm${PWM_NUM}"
echo ${PERIOD_DEFAULT_VALUE} > period
echo ${CURRENT_DUTY_CYCLE} > duty_cycle
echo 1 > enable

echo "FAN work at:"
echo "    1. $((1000000000 / ${PERIOD_DEFAULT_VALUE})) Hz"
echo "    2. $((CURRENT_DUTY_CYCLE * 100 / ${PERIOD_DEFAULT_VALUE})) %"
