    RSEG    CODE:CODE(2)
	THUMB
    
    PUBLIC __hal_app_jump
    
__hal_app_jump
    cpsid   i                       ;  �ر��ж�

    ldr     r1, =0xE000ED08         ;  �л�������Ӧ�ó������ʼ��ַ
    str     r0, [r1]

    movs    r2, #0x00               ;  �л�����ģʽ����������Ȩ�����߳�ģʽ  ʹ��MSP
    msr     control, r2

    ldr     r1, [r0]                ;  ���ö�ջָ��
    mov     sp, r1

    cpsie   i                       ;  ʹ���ж�
    ldr     r0, [r0, #4]            ;  ���õ�ǰPC��ֵ����ʼ�����µ�Ӧ�ó���
    bx      r0
    
    END
    