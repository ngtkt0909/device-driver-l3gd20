/**
 * @file		l3gd20.h
 * @brief		Device Driver for L3GD20
 *
 * @author		T. Ngtk
 * @copyright	Copyright (c) 2017 T. Ngtk
 *
 * @par License
 *	Released under the MIT and GPL Licenses.
 *	- https://github.com/ngtkt0909/device-driver-l3gd20/blob/master/LICENSE-MIT
 *	- https://github.com/ngtkt0909/device-driver-l3gd20/blob/master/LICENSE-GPL
 */

#ifndef __L3GD20_H__
#define __L3GD20_H__

#define ADDR_L3GD20		0x6A

#define REG_WHO_AM_I	0x0F
#define REG_CTRL_REG1	0x20
#define REG_OUT_X_L		0x28
#define REG_OUT_X_H		0x29
#define REG_OUT_Y_L		0x2A
#define REG_OUT_Y_H		0x2B
#define REG_OUT_Z_L		0x2C
#define REG_OUT_Z_H		0x2D

#define VAL_WHO_AM_I	0xD4
#define VAL_CTRL_REG1	0x0F

#define DPS_PER_LSB		0.00875

#endif	/* __L3GD20_H__ */