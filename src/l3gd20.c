/**
 * @file		l3gd20.c
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

#include <linux/delay.h> 
#include <linux/device.h>
#include <linux/kernel.h> 
#include <linux/mutex.h> 
#include <linux/module.h> 
#include <linux/slab.h> 
#include <linux/i2c.h> 
#include <linux/string.h>
#include "l3gd20.h"

/*------------------------------------------------------------------------------
	Type Definition
------------------------------------------------------------------------------*/
struct i2c_sns_device {
	struct i2c_client *client;
};

/*------------------------------------------------------------------------------
	Global Variables
------------------------------------------------------------------------------*/
static const struct i2c_device_id i2c_sns_id[] = {
	{ "i2c_l3gd20", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, i2c_sns_id);

static const unsigned short i2c_sns_addr[] = {
	ADDR_L3GD20,
	I2C_CLIENT_END
};

static int16_t i2c_sns_read(struct i2c_client *client, uint8_t reg_h, uint8_t reg_l)
{
	uint8_t val_h, val_l;

	val_h = i2c_smbus_read_byte_data(client, reg_h);
	val_l = i2c_smbus_read_byte_data(client, reg_l);

	return (int16_t)(((val_h & 0xFF) << 8) | (val_l & 0xFF));
}

/*------------------------------------------------------------------------------
	Functions (Internal)
------------------------------------------------------------------------------*/
static int gyro_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_sns_device *data = (struct i2c_sns_device *)dev_get_drvdata(dev);
	int16_t val_x, val_y, val_z;

	val_x = i2c_sns_read(data->client, REG_OUT_X_H, REG_OUT_X_L);
	val_y = i2c_sns_read(data->client, REG_OUT_Y_H, REG_OUT_Y_L);
	val_z = i2c_sns_read(data->client, REG_OUT_Z_H, REG_OUT_Z_L);

	return sprintf(buf, "%d,%d,%d", val_x, val_y, val_z);
}
static DEVICE_ATTR(gyro, S_IRUSR | S_IRGRP, gyro_show, NULL);

/*------------------------------------------------------------------------------
	Functions (External)
------------------------------------------------------------------------------*/
static int i2c_sns_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct i2c_sns_device *dev;
	uint8_t val;
	int ret;

	printk( KERN_INFO "probing ... addr=%d\n", client->addr);

	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK)) {
		printk(KERN_ERR "%s: needed i2c functionality is not supported\n", __func__);
		return -ENODEV;
	}

	/* Check connection */
	val = i2c_smbus_read_byte_data(client, REG_WHO_AM_I);
	if (val != VAL_WHO_AM_I) {
		return -ENODEV;
	}

	/* Initialize device */
	ret = i2c_smbus_write_byte_data(client, REG_CTRL_REG1, VAL_CTRL_REG1);
	if (ret < 0) {
		printk(KERN_ERR "%s: failed to initialize device\n", __func__);
		return -ENODEV;
	}

	dev = kzalloc(sizeof(struct i2c_sns_device), GFP_KERNEL);
	if (dev == NULL) {
		printk(KERN_ERR "%s: no memory\n", __func__);
		return -ENOMEM;
	}

	dev->client = client;
	i2c_set_clientdata(client, dev);

	ret = device_create_file(&client->dev, &dev_attr_gyro);
	if (ret) {
		printk(KERN_ERR "failed to add gyro attribute\n");
	}
	
	return 0;
}

static int i2c_sns_remove(struct i2c_client *client)
{
	struct i2c_sns_device *dev;

	printk(KERN_INFO "removing ... \n");

	device_remove_file(&client->dev,  &dev_attr_gyro);

	dev = (struct i2c_sns_device *)i2c_get_clientdata(client);
	kfree(dev);

	return 0;
}

static struct i2c_driver i2c_sns_driver = {
	.probe    = i2c_sns_probe,
	.remove   = i2c_sns_remove,
	.id_table = i2c_sns_id,
	.address_list = i2c_sns_addr,
	.driver   = {
		.owner = THIS_MODULE,
		.name = "i2c_l3gd20",
	},
};

module_i2c_driver(i2c_sns_driver);

MODULE_DESCRIPTION("I2C L3GD20 driver");
MODULE_LICENSE("Dual MIT/GPL");
