/*
 * GlobalDefs.h
 *
 * Created: 2015/04/25 07:49:05 PM
 *  Author: Matt
 */ 


#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

typedef struct
{
	//------------BMS DATA----------------//
	//BMS Data Flags
	uint8_t		BMSData_warnings[7];		//Warnings and flags
	//BMS voltages & IDs			BIT
	uint8_t		maxVoltage;			//4
	uint8_t		maxVoltageID;		//5
	uint8_t		minVoltage;			//2
	uint8_t		minVoltageID;		//3
	uint16_t	packVoltage;		//0,1		//Voltages
	
	//BMS Charge Limits
	uint16_t	current;			//0,1
	uint16_t	chargeLimit;		//2,3
	uint16_t	dischargeLimit;		//4,5
	
	//BMS Battery Energy
	uint32_t	batteryEnergyIn;	//0-3
	uint32_t	batteryEnergyOut;	//4-7
	
	//BMS Battery Params
	uint8_t		SOC;				//0
	uint16_t	DOD;				//1,2	//discharge depth
	uint16_t	capacity;			//3,4		//capacity of bank
	//byte 5 blank
	uint8_t		SOH;				//6		//state of charge
	
	//Temperatures
	uint8_t		minTempID;			//0
	//byte 1 blank
	uint8_t		minTemperature;		//2
	uint8_t		temperature;		//3
	uint8_t		maxTemperature;		//4
	uint8_t		maxTempID;			//5
	
	//Resistances
	uint16_t	packResistance;		//0,1
	uint8_t		minRes;				//2
	uint8_t		minResID;			//3
	uint8_t		maxRes;				//4
	uint8_t		maxResID;			//5
	//------------MPPT DATA----------------//
	uint16_t		Vin;			//0&1
	uint16_t		Iin;			//2&3
	uint16_t		Vout;			//4&5
	uint8_t			Tamb;			//6
	uint8_t			mppt_flags;		//bits 4-7 of byte 1
	
	//------------SPEED DATA----------------//
	uint8_t			avgSpeed;		//0
	uint8_t			hesSPeed;		//1
	uint16_t		hesRPM;			//2,3
	uint8_t			motorSpeed;		//4
	uint16_t		motorRPM;		//5,6
	uint8_t			statusFlags;	//7
	
}GlobalVars;



#endif /* GLOBALDEFS_H_ */