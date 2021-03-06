#pragma once

#include "Common.h"
#include <gpsapi.h>
#include <cmath>
#include "Device.h"

/**
 *	<<singleton>>
 *	GPS
 *		Retrieve Phone position via RIL/GPS
 **/
class GPS
{
	public:
		static GPS *self(DWORD dwTimeout, DWORD dwMaximumAge);
		BOOL	GpsReady();

		BOOL	getGPS(GPS_POSITION *);

		void	Stop();
		BOOL	Start();

		DOUBLE  VincentFormula(DOUBLE lat1, DOUBLE lon1, DOUBLE lat2, DOUBLE lon2);

	protected:
		GPS();	// .ctor

		static GPS *_instance;	// Global self
		
		/**
		* Inizializza l'oggetto, torna FALSE se l'inizializzazione fallisce.
		* dwTimeout e dwMaximumAge sono in millisecondi e rappresentano rispettivamente
		* il tempo massimo di attesa per ottenere una posizione valida e l'eta massima
		* della coordinata richiesta.
		**/
		BOOL	Initialize(DWORD dwTimeout, DWORD dwMaximumAge);
		BOOL	RefreshData();	// Try to refresh data

	private: ~GPS();	// .dtor

	private:
		DWORD	_dwTimeout;			// constructor parameters
		DWORD	_dwMaximumAge;
		DWORD	_dwTickCount;		// old request tick count

		HANDLE	_hMutex;			// mutex
		INT		_iReference;		// Reference counter

		HANDLE	_hGpsDevice;		// device handle

		GPS_POSITION	_gpsPosition;
		
		DWORD	_dwLastGps;			// time of last GPS
		BOOL	bInitialized;

		Device *deviceObj;

		static	BOOL _bGpsReady;	// GPS Ready
		static volatile LONG lLock;	// Il nostro mutex
};
