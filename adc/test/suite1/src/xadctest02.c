//*****************************************************************************
//
//! @page xadc_testcase xadc register test
//!
//! File: @ref xadctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xadc sub component.<br><br>
//! - \p Board: FREEDOM-KL25Z <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>RS232 cable.<br>
//! <br>TTL to RS232 convert board.<br>
//! <br><img src="\..\..\..\..\doc\images\Freedom_test_connect.png" /><br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xadc_register03
//! .
//! \file xsysctltest02.c
//! \brief xsysctl test source file
//! \file xsysctltest02.h
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_adc.h"
#include "xadc.h"

//*****************************************************************************
//
//!\page test_xadc_register03 test_xadc_interrupt
//!
//!<h2>Description</h2>
//! 0 Interrupt state and data get test.
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xadc002 register test.
//!
//! \return the desccription of the xadc002 test.
//
//*****************************************************************************
static char* xadc002GetTest( void )
{
    return "xadc, 002, xadc interrupt test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xadc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002Setup( void )
{
    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC);

    //
    // Enable GPIO clock 
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // configure GPIO pin as ADC function
    //
    xSPinTypeADC(ADC0, PE20);

    //
    // Set ADC clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, 8);
}
//*****************************************************************************
//
//! \brief ADC0 Interrupt Handler.
//!
//! If users want to user the ADC0 Callback feature, Users should promise 
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long ADC0IntFucntion(void *pvCBData,
                              unsigned long ulEvent,
                              unsigned long ulMsgParam,
                              void *pvMsgData)
{

    TestEmitToken('T');
	return 0;
}

//*****************************************************************************
//
//! \brief  adc api interrupt state and data get test.
//!
//! \return None.
//
//*****************************************************************************
static void adcIntTest(void)
{

	//
    // Set the length of converter
    //
    // ADCConverLenSet(ADC1_BASE, 1, 1);
    //
    // Test ADC configure API
    //
    // ADCSequenceIndexSet(ADC1_BASE, ulAdcSeqNo, ulAdcSeqNo);
    // ADCSampLenSet(ADC1_BASE, 14, ADC_SAMPTIME_7_5_CYCLE);

    //
    // A/D interrupt enable 
    //
    ADCIntEnable(ADC_BASE, ADC_INT_END_CONVERSION);
    xIntEnable(INT_ADC);
    xADCIntCallbackInit(ADC_BASE, ADC0IntFucntion);

    //
    // A/D configure 
    //
    ADCConfigure(ADC_BASE, ADC_INPUT_SINGLE, ADC_OP_CONTINUOUS, ADC_TRIGGER_PROCESSOR);
    ADCProcessorTrigger(ADC_BASE);
    TestAssertQBreak("T", "xadc interrupt function error!", 0xFFFFFFFF);
}
//*****************************************************************************
//
//! \brief xadc002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002Execute( void )
{
    adcIntTest();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xadc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002TearDown( void )
{
    
}

//
// xadc002 register test case struct.
//
const tTestCase sTestXAdc002Register = {
    xadc002GetTest,
    xadc002Setup,
    xadc002TearDown,
    xadc002Execute

};

//
// ADC test suits.
//
const tTestCase * const psPatternXadc02[] =
{
    &sTestXAdc002Register,
    0
};


