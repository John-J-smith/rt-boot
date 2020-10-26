    RSEG    CODE:CODE(2)
	THUMB
    
    PUBLIC __hal_app_jump
    
__hal_app_jump
    cpsid   i                       ;  关闭中断

    ldr     r1, =0xE000ED08         ;  切换向量表到应用程序的起始地址
    str     r0, [r1]

    movs    r2, #0x00               ;  切换工作模式，工作到特权级的线程模式  使用MSP
    msr     control, r2

    ldr     r1, [r0]                ;  设置堆栈指针
    mov     sp, r1

    cpsie   i                       ;  使能中断
    ldr     r0, [r0, #4]            ;  设置当前PC的值，开始运行新的应用程序
    bx      r0
    
    END
    