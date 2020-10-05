#include "sys_intr.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"


//#define VTC_BASEADDR XPAR_MIZ702_VTG_VGA_0_BASEADDR
#define DDR_BASEADDR        0x00100000
//#define UART_BASEADDR		0xe0001000
#define VDMA_BASEADDR       XPAR_AXI_VDMA_0_BASEADDR
#define H_STRIDE            1280
#define H_ACTIVE            1280
#define V_ACTIVE            720
#define pi					3.14159265358
#define COUNTS_PER_SECOND	(XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ)/64


#define VIDEO_LENGTH  (H_STRIDE*V_ACTIVE)
#define VIDEO_BASEADDR0 DDR_BASEADDR + 0x2000000
#define VIDEO_BASEADDR1 DDR_BASEADDR + 0x3000000
#define VIDEO_BASEADDR2 DDR_BASEADDR + 0x4000000

u32 *BufferPtr[3];

unsigned int srcBuffer0 = (XPAR_PS7_DDR_0_S_AXI_BASEADDR  + 0x1000000);
unsigned int srcBuffer1 = (XPAR_PS7_DDR_0_S_AXI_BASEADDR  + 0x2000000);

int run_triple_frame_buffer(XAxiVdma* InstancePtr, int DeviceId, int hsize,
		int vsize, int buf_base_addr, int number_frame_count,
		int enable_frm_cnt_intr);

void ov5640_init_rgb(void);
int Miz702_EMIO_init(void);

int main(void)
{

	u32 Status_VDMA0;
	u32 Status_VDMA1;

	Miz702_EMIO_init();
	ov5640_init_rgb();

	XAxiVdma InstancePtr;

	xil_printf("Starting the first VDMA \n\r");

	Status_VDMA0 = run_triple_frame_buffer(&InstancePtr, 0, 1280, 720,
			srcBuffer0, 2, 0);
	Status_VDMA1 = run_triple_frame_buffer(&InstancePtr, 1, 1280, 720,
			srcBuffer1, 2, 0);

	if (Status_VDMA0 != XST_SUCCESS) {
		xil_printf("VDMA0:Transfer of frames failed with error = %d\r\n",Status_VDMA0);
		return XST_FAILURE;
	} else {
		xil_printf("VDMA0:Transfer of frames started \r\n");
	}

	if (Status_VDMA1 != XST_SUCCESS) {
		xil_printf("VDMA1:Transfer of frames failed with error = %d\r\n",Status_VDMA1);
		return XST_FAILURE;
	} else {
		xil_printf("VDMA1:Transfer of frames started \r\n");
	}

	print("TEST PASS\r\n");

	while(1){};

	return XST_SUCCESS;
}


