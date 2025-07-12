******************************************************************************
                  TI ARM Linker Unix v20.2.7                   
******************************************************************************
>> Linked Sat Jul 12 13:58:16 2025

OUTPUT FILE NAME:   <build/output.elf>
ENTRY POINT SYMBOL: "_c_int00"  address: 00006234


MEMORY CONFIGURATION

         name            origin    length      used     unused   attr    fill
----------------------  --------  ---------  --------  --------  ----  --------
  RAM                   00000020   ffffffe0  00006c58  ffff9388  RWIX


SEGMENT ALLOCATION MAP

run origin  load origin   length   init length attrs members
----------  ----------- ---------- ----------- ----- -------
00000020    00000020    00006c58   00006c58    r-x
  00000020    00000020    00006a38   00006a38    r-x .text
  00006a58    00006a58    00000200   00000200    r-- .const
  00006c58    00006c58    00000020   00000020    r-x .intvecs


SECTION ALLOCATION MAP

 output                                  attributes/
section   page    origin      length       input sections
--------  ----  ----------  ----------   ----------------
.text      0    00000020    00006a38     
                  00000020    00002cdc     sys_selftest.obj (.text)
                  00002cfc    00000b78     system.obj (.text)
                  00003874    00000a54     sys_vim.obj (.text)
                  000042c8    000008b0     pinmux.obj (.text)
                  00004b78    00000664     errata_SSWF021_45.obj (.text)
                  000051dc    000005bc     esm.obj (.text)
                  00005798    00000484     gio.obj (.text)
                  00005c1c    0000034c     sys_core.obj (.text)
                  00005f68    000002cc     sys_vim.obj (.text:retain)
                  00006234    00000288     sys_startup.obj (.text:retain)
                  000064bc    0000021c     notification.obj (.text)
                  000066d8    00000114     esm.obj (.text:retain)
                  000067ec    000000e8     dabort.obj (.text)
                  000068d4    000000e0     sys_pmu.obj (.text)
                  000069b4    00000054     sys_main.obj (.text)
                  00006a08    00000044     rtsv7R4_T_be_v3D16_eabi.lib : autoinit.c.obj (.text:__TI_auto_init_nobinit_nopinit:__TI_auto_init_nobinit_nopinit)
                  00006a4c    00000004                                 : exit.c.obj (.text:abort:abort)
                  00006a50    00000004     sys_phantom.obj (.text:retain)
                  00006a54    00000004     sys_startup.obj (.text)

.const     0    00006a58    00000200     
                  00006a58    00000200     sys_vim.obj (.const:s_vim_init)

.init_array 
*          0    00000020    00000000     UNINITIALIZED

__llvm_prf_cnts 
*          0    00000020    00000000     UNINITIALIZED

.intvecs   0    00006c58    00000020     
                  00006c58    00000020     sys_intvecs.obj (.intvecs)

MODULE SUMMARY

       Module                  code    ro data   rw data
       ------                  ----    -------   -------
    build/
       sys_selftest.obj        11484   0         0      
       sys_vim.obj             3360    512       0      
       system.obj              2936    0         0      
       pinmux.obj              2224    0         0      
       esm.obj                 1744    0         0      
       errata_SSWF021_45.obj   1636    0         0      
       gio.obj                 1156    0         0      
       sys_core.obj            844     0         0      
       sys_startup.obj         652     0         0      
       notification.obj        540     0         0      
       dabort.obj              232     0         0      
       sys_pmu.obj             224     0         0      
       sys_main.obj            84      0         0      
       sys_intvecs.obj         32      0         0      
       sys_phantom.obj         4       0         0      
    +--+-----------------------+-------+---------+---------+
       Total:                  27152   512       0      
                                                        
    /opt/ti-cgt-arm_20.2.7.LTS/lib/rtsv7R4_T_be_v3D16_eabi.lib
       autoinit.c.obj          68      0         0      
       exit.c.obj              4       0         0      
    +--+-----------------------+-------+---------+---------+
       Total:                  72      0         0      
                                                        
    +--+-----------------------+-------+---------+---------+
       Grand Total:            27224   512       0      


GLOBAL SYMBOLS: SORTED ALPHABETICALLY BY Name 

address   name                                
-------   ----                                
00006a4d  C$$EXIT                             
UNDEFED   SHT$$INIT_ARRAY$$Base               
UNDEFED   SHT$$INIT_ARRAY$$Limit              
UNDEFED   __TI_CINIT_Base                     
UNDEFED   __TI_CINIT_Limit                    
UNDEFED   __TI_Handler_Table_Base             
UNDEFED   __TI_Handler_Table_Limit            
00005f60  __TI_PINIT_Base                     
00005f64  __TI_PINIT_Limit                    
00006a09  __TI_auto_init_nobinit_nopinit      
ffffffff  __TI_pprof_out_hndl                 
ffffffff  __TI_prof_data_size                 
ffffffff  __TI_prof_data_start                
00000020  __TI_static_base__                  
ffffffff  __binit__                           
ffffffff  __c_args__                          
00000020  __start___llvm_prf_cnts             
00000020  __stop___llvm_prf_cnts              
00006234  _c_int00                            
00005e78  _coreClearAuxiliaryDataFault_       
00005e8c  _coreClearAuxiliaryInstructionFault_
00005e50  _coreClearDataFaultAddress_         
00005e28  _coreClearDataFault_                
00005e64  _coreClearInstructionFaultAddress_  
00005e3c  _coreClearInstructionFault_         
00005dbc  _coreDisableEventBusExport_         
00005e00  _coreDisableFlashEcc_               
00005ddc  _coreDisableRamEcc_                 
00005dac  _coreEnableEventBusExport_          
00005dec  _coreEnableFlashEcc_                
00005e10  _coreEnableIrqVicOffset_            
00005dcc  _coreEnableRamEcc_                  
00005d94  _coreEnableVfp_                     
00005e70  _coreGetAuxiliaryDataFault_         
00005e84  _coreGetAuxiliaryInstructionFault_  
00005e48  _coreGetDataFaultAddress_           
00005e20  _coreGetDataFault_                  
00005e5c  _coreGetInstructionFaultAddress_    
00005e34  _coreGetInstructionFault_           
00005c1c  _coreInitRegisters_                 
00005d28  _coreInitStackPointer_              
000067ec  _dabort                             
00005ea0  _disable_FIQ_interrupt_             
00005ea8  _disable_IRQ_interrupt_             
00005e98  _disable_interrupt_                 
00005eb0  _enable_interrupt_                  
00005f40  _errata_CORTEXR4_57_                
00005f50  _errata_CORTEXR4_66_                
00004b78  _errata_SSWF021_45_both_plls        
00004d6c  _errata_SSWF021_45_pll1             
00004ee4  _errata_SSWF021_45_pll2             
00005eb8  _esmCcmErrorsClear_                 
00005d74  _getCPSRValue_                      
00005d7c  _gotoCPUIdle_                       
00006930  _pmuDisableCountersGlobal_          
00006920  _pmuEnableCountersGlobal_           
0000698c  _pmuGetCycleCount_                  
00006994  _pmuGetEventCount_                  
000069a0  _pmuGetOverflow_                    
000068d4  _pmuInit_                           
00006960  _pmuResetCounters_                  
00006940  _pmuResetCycleCounter_              
00006950  _pmuResetEventCounters_             
00006980  _pmuSetCountEvent_                  
00006970  _pmuStartCounters_                  
00006978  _pmuStopCounters_                   
UNDEFED   _system_post_cinit                  
00006a4d  abort                               
0000126c  adc1ParityCheck                     
00001358  adc2ParityCheck                     
00006524  adcNotification                     
ffffffff  binit                               
00001410  can1ParityCheck                     
000014e8  can2ParityCheck                     
000015b0  can3ParityCheck                     
00006538  canErrorNotification                
00006560  canMessageNotification              
0000654c  canStatusChangeNotification         
00000030  ccmSelfCheck                        
000026fc  ccmr4GetConfigValue                 
00000938  checkB0RAMECC                       
00000b28  checkB1RAMECC                       
00001c18  checkClockMonitor                   
00000d18  checkFlashECC                       
00001cf4  checkFlashEEPROMECC                 
00001e8c  checkPLL1Slip                       
00001f8c  checkPLL2Slip                       
00002050  checkRAMAddrParity                  
000019d0  checkRAMECC                         
0000215c  checkRAMUERRTest                    
000007bc  checkefcSelfTest                    
00000234  cpuSelfTest                         
00000dfc  cpuSelfTestFail                     
00006664  crcNotification                     
00003794  customTrimLPO                       
00000df4  custom_dabort                       
00006574  dccNotification                     
00002b58  disableParity                       
000066c4  dmaGroupANotification               
00000eac  dmaParityCheck                      
000066b0  ecapNotification                    
0000663c  edgeNotification                    
00000660  efcCheck                            
00002660  efcGetConfigValue                   
00000794  efcSelfTest                         
000006e8  efcStuckZeroTest                    
00002ad0  enableParity                        
0000669c  eqepNotification                    
0000276c  errata_PBIST_4                      
00005360  esmActivateNormalOperation          
00005434  esmClearStatus                      
00005474  esmClearStatusBuffer                
00005328  esmDisableError                     
00005398  esmDisableInterrupt                 
00005300  esmEnableError                      
00005370  esmEnableInterrupt                  
0000556c  esmEnterSelfTest                    
000052e4  esmError                            
00005644  esmGetConfigValue                   
000054b0  esmGetStatus                        
00005534  esmGetStatusBuffer                  
000064bc  esmGroup1Notification               
000064cc  esmGroup2Notification               
000066d8  esmHighInterrupt                    
000051dc  esmInit                             
000055f4  esmSelfTestStatus                   
00005490  esmSetCounterPreloadValue           
000053c0  esmSetInterruptLevel                
00005350  esmTriggerErrorPinReset             
00006678  etpwmNotification                   
00006688  etpwmTripNotification               
000022c4  fmcBus1ParityCheck                  
0000085c  fmcBus2Check                        
00000898  fmcECCcheck                         
000059f8  gioDisableNotification              
00005990  gioEnableNotification               
000058f8  gioGetBit                           
00005a60  gioGetConfigValue                   
00005920  gioGetPort                          
00005798  gioInit                             
00006588  gioNotification                     
00005888  gioSetBit                           
00005868  gioSetDirection                     
000058d8  gioSetPort                          
00005938  gioToggleBit                        
00006a54  handlePLLLockFail                   
00000f58  het1ParityCheck                     
000010c0  het2ParityCheck                     
00006650  hetNotification                     
00001004  htu1ParityCheck                     
000011bc  htu2ParityCheck                     
0000659c  i2cNotification                     
000065b0  linNotification                     
000069b4  main                                
00002e6c  mapClocks                           
00000174  memoryInit                          
000064dc  memoryPort0TestFailNotification     
000064f8  memoryPort1TestFailNotification     
00001684  mibspi1ParityCheck                  
0000178c  mibspi3ParityCheck                  
000018b0  mibspi5ParityCheck                  
000065d8  mibspiGroupNotification             
000065c4  mibspiNotification                  
000042c8  muxInit                             
000023ec  pbistFail                           
00002470  pbistGetConfigValue                 
000005a8  pbistIsTestCompleted                
000005d4  pbistIsTestPassed                   
00000608  pbistPortTestStatus                 
000004ac  pbistRun                            
000002cc  pbistSelfCheck                      
00000578  pbistStop                           
00002e18  periphInit                          
00006a50  phantomInterrupt                    
00004764  pinmuxGetConfigValue                
00006624  pwmNotification                     
00006c58  resetEntry                          
00006514  rtiNotification                     
000065ec  sciNotification                     
00000020  selftestFailNotification            
00002dd8  setupFlash                          
00002cfc  setupPLL                            
00006614  spiEndNotification                  
00006600  spiNotification                     
00003658  sramGetConfigValue                  
000025bc  stcGetConfigValue                   
000001b8  stcSelfCheck                        
00000df8  stcSelfCheckFail                    
00003090  systemGetConfigValue                
00002f94  systemInit                          
00003060  systemPowerDown                     
000034ac  tcmflashGetConfigValue              
00002d5c  trimLPO                             
00003948  vimChannelMap                       
00003bb4  vimDisableInterrupt                 
000039ec  vimEnableInterrupt                  
00003c60  vimGetConfigValue                   
00003874  vimInit                             
00000e00  vimParityCheck                      
00005f68  vimParityErrorHandler               


GLOBAL SYMBOLS: SORTED BY Symbol Address 

address   name                                
-------   ----                                
00000020  __TI_static_base__                  
00000020  __start___llvm_prf_cnts             
00000020  __stop___llvm_prf_cnts              
00000020  selftestFailNotification            
00000030  ccmSelfCheck                        
00000174  memoryInit                          
000001b8  stcSelfCheck                        
00000234  cpuSelfTest                         
000002cc  pbistSelfCheck                      
000004ac  pbistRun                            
00000578  pbistStop                           
000005a8  pbistIsTestCompleted                
000005d4  pbistIsTestPassed                   
00000608  pbistPortTestStatus                 
00000660  efcCheck                            
000006e8  efcStuckZeroTest                    
00000794  efcSelfTest                         
000007bc  checkefcSelfTest                    
0000085c  fmcBus2Check                        
00000898  fmcECCcheck                         
00000938  checkB0RAMECC                       
00000b28  checkB1RAMECC                       
00000d18  checkFlashECC                       
00000df4  custom_dabort                       
00000df8  stcSelfCheckFail                    
00000dfc  cpuSelfTestFail                     
00000e00  vimParityCheck                      
00000eac  dmaParityCheck                      
00000f58  het1ParityCheck                     
00001004  htu1ParityCheck                     
000010c0  het2ParityCheck                     
000011bc  htu2ParityCheck                     
0000126c  adc1ParityCheck                     
00001358  adc2ParityCheck                     
00001410  can1ParityCheck                     
000014e8  can2ParityCheck                     
000015b0  can3ParityCheck                     
00001684  mibspi1ParityCheck                  
0000178c  mibspi3ParityCheck                  
000018b0  mibspi5ParityCheck                  
000019d0  checkRAMECC                         
00001c18  checkClockMonitor                   
00001cf4  checkFlashEEPROMECC                 
00001e8c  checkPLL1Slip                       
00001f8c  checkPLL2Slip                       
00002050  checkRAMAddrParity                  
0000215c  checkRAMUERRTest                    
000022c4  fmcBus1ParityCheck                  
000023ec  pbistFail                           
00002470  pbistGetConfigValue                 
000025bc  stcGetConfigValue                   
00002660  efcGetConfigValue                   
000026fc  ccmr4GetConfigValue                 
0000276c  errata_PBIST_4                      
00002ad0  enableParity                        
00002b58  disableParity                       
00002cfc  setupPLL                            
00002d5c  trimLPO                             
00002dd8  setupFlash                          
00002e18  periphInit                          
00002e6c  mapClocks                           
00002f94  systemInit                          
00003060  systemPowerDown                     
00003090  systemGetConfigValue                
000034ac  tcmflashGetConfigValue              
00003658  sramGetConfigValue                  
00003794  customTrimLPO                       
00003874  vimInit                             
00003948  vimChannelMap                       
000039ec  vimEnableInterrupt                  
00003bb4  vimDisableInterrupt                 
00003c60  vimGetConfigValue                   
000042c8  muxInit                             
00004764  pinmuxGetConfigValue                
00004b78  _errata_SSWF021_45_both_plls        
00004d6c  _errata_SSWF021_45_pll1             
00004ee4  _errata_SSWF021_45_pll2             
000051dc  esmInit                             
000052e4  esmError                            
00005300  esmEnableError                      
00005328  esmDisableError                     
00005350  esmTriggerErrorPinReset             
00005360  esmActivateNormalOperation          
00005370  esmEnableInterrupt                  
00005398  esmDisableInterrupt                 
000053c0  esmSetInterruptLevel                
00005434  esmClearStatus                      
00005474  esmClearStatusBuffer                
00005490  esmSetCounterPreloadValue           
000054b0  esmGetStatus                        
00005534  esmGetStatusBuffer                  
0000556c  esmEnterSelfTest                    
000055f4  esmSelfTestStatus                   
00005644  esmGetConfigValue                   
00005798  gioInit                             
00005868  gioSetDirection                     
00005888  gioSetBit                           
000058d8  gioSetPort                          
000058f8  gioGetBit                           
00005920  gioGetPort                          
00005938  gioToggleBit                        
00005990  gioEnableNotification               
000059f8  gioDisableNotification              
00005a60  gioGetConfigValue                   
00005c1c  _coreInitRegisters_                 
00005d28  _coreInitStackPointer_              
00005d74  _getCPSRValue_                      
00005d7c  _gotoCPUIdle_                       
00005d94  _coreEnableVfp_                     
00005dac  _coreEnableEventBusExport_          
00005dbc  _coreDisableEventBusExport_         
00005dcc  _coreEnableRamEcc_                  
00005ddc  _coreDisableRamEcc_                 
00005dec  _coreEnableFlashEcc_                
00005e00  _coreDisableFlashEcc_               
00005e10  _coreEnableIrqVicOffset_            
00005e20  _coreGetDataFault_                  
00005e28  _coreClearDataFault_                
00005e34  _coreGetInstructionFault_           
00005e3c  _coreClearInstructionFault_         
00005e48  _coreGetDataFaultAddress_           
00005e50  _coreClearDataFaultAddress_         
00005e5c  _coreGetInstructionFaultAddress_    
00005e64  _coreClearInstructionFaultAddress_  
00005e70  _coreGetAuxiliaryDataFault_         
00005e78  _coreClearAuxiliaryDataFault_       
00005e84  _coreGetAuxiliaryInstructionFault_  
00005e8c  _coreClearAuxiliaryInstructionFault_
00005e98  _disable_interrupt_                 
00005ea0  _disable_FIQ_interrupt_             
00005ea8  _disable_IRQ_interrupt_             
00005eb0  _enable_interrupt_                  
00005eb8  _esmCcmErrorsClear_                 
00005f40  _errata_CORTEXR4_57_                
00005f50  _errata_CORTEXR4_66_                
00005f60  __TI_PINIT_Base                     
00005f64  __TI_PINIT_Limit                    
00005f68  vimParityErrorHandler               
00006234  _c_int00                            
000064bc  esmGroup1Notification               
000064cc  esmGroup2Notification               
000064dc  memoryPort0TestFailNotification     
000064f8  memoryPort1TestFailNotification     
00006514  rtiNotification                     
00006524  adcNotification                     
00006538  canErrorNotification                
0000654c  canStatusChangeNotification         
00006560  canMessageNotification              
00006574  dccNotification                     
00006588  gioNotification                     
0000659c  i2cNotification                     
000065b0  linNotification                     
000065c4  mibspiNotification                  
000065d8  mibspiGroupNotification             
000065ec  sciNotification                     
00006600  spiNotification                     
00006614  spiEndNotification                  
00006624  pwmNotification                     
0000663c  edgeNotification                    
00006650  hetNotification                     
00006664  crcNotification                     
00006678  etpwmNotification                   
00006688  etpwmTripNotification               
0000669c  eqepNotification                    
000066b0  ecapNotification                    
000066c4  dmaGroupANotification               
000066d8  esmHighInterrupt                    
000067ec  _dabort                             
000068d4  _pmuInit_                           
00006920  _pmuEnableCountersGlobal_           
00006930  _pmuDisableCountersGlobal_          
00006940  _pmuResetCycleCounter_              
00006950  _pmuResetEventCounters_             
00006960  _pmuResetCounters_                  
00006970  _pmuStartCounters_                  
00006978  _pmuStopCounters_                   
00006980  _pmuSetCountEvent_                  
0000698c  _pmuGetCycleCount_                  
00006994  _pmuGetEventCount_                  
000069a0  _pmuGetOverflow_                    
000069b4  main                                
00006a09  __TI_auto_init_nobinit_nopinit      
00006a4d  C$$EXIT                             
00006a4d  abort                               
00006a50  phantomInterrupt                    
00006a54  handlePLLLockFail                   
00006c58  resetEntry                          
ffffffff  __TI_pprof_out_hndl                 
ffffffff  __TI_prof_data_size                 
ffffffff  __TI_prof_data_start                
ffffffff  __binit__                           
ffffffff  __c_args__                          
ffffffff  binit                               
UNDEFED   SHT$$INIT_ARRAY$$Base               
UNDEFED   SHT$$INIT_ARRAY$$Limit              
UNDEFED   __TI_CINIT_Base                     
UNDEFED   __TI_CINIT_Limit                    
UNDEFED   __TI_Handler_Table_Base             
UNDEFED   __TI_Handler_Table_Limit            
UNDEFED   _system_post_cinit                  

[200 symbols]
