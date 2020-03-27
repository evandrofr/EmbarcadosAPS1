#include "asf.h"
#include "musicas.h"

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED1_PIO			PIOA
#define LED1_PIO_ID			ID_PIOA
#define LED1_PIO_IDX		0
#define LED1_PIO_IDX_MASK	(1 << LED1_PIO_IDX)

#define LED2_PIO			PIOC
#define LED2_PIO_ID			ID_PIOC
#define LED2_PIO_IDX		30
#define LED2_PIO_IDX_MASK	(1 << LED2_PIO_IDX)

#define LED3_PIO			PIOB
#define LED3_PIO_ID			ID_PIOB
#define LED3_PIO_IDX		2
#define LED3_PIO_IDX_MASK	(1 << LED3_PIO_IDX)

#define LED_PIO			     PIOC
#define LED_PIO_ID			ID_PIOC
#define LED_PIO_IDX			   8
#define LED_PIO_IDX_MASK	(1 << LED_PIO_IDX)


// Configuracoes do botoes

#define BUT_PIO				PIOA
#define BUT_PIO_ID			ID_PIOA
#define BUT_PIO_IDX			11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

#define BUT1_PIO			PIOD
#define BUT1_PIO_ID			ID_PIOD
#define BUT1_PIO_IDX		28
#define BUT1_PIO_IDX_MASK	(1u << BUT1_PIO_IDX)

#define BUT3_PIO			PIOA
#define BUT3_PIO_ID			ID_PIOA
#define BUT3_PIO_IDX		19
#define BUT3_PIO_IDX_MASK	(1u << BUT3_PIO_IDX)

#define BUT2_PIO			PIOC
#define BUT2_PIO_ID			ID_PIOC
#define BUT2_PIO_IDX		31
#define BUT2_PIO_IDX_MASK	(1u << BUT2_PIO_IDX)

// Configuracoes Buzzer
#define BUZZ_PIO			PIOD
#define BUZZ_PIO_ID			ID_PIOD
#define BUZZ_PIO_IDX		30
#define BUZZ_PIO_IDX_MASK	(1u << BUZZ_PIO_IDX)

#define NMUS                3



void init(void);
void tone(int freq, int dur);
void but_callback(void);
void but1_callback(void);
void but2_callback(void);
void but3_callback(void);
/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

const int buzzer = 10; 
const int songspeed = 1.5;

volatile char but_flag = 0;
volatile char but1_flag = 0;
volatile char but2_flag = 0;
volatile char but3_flag = 0; 
char pause = 1;
//*****************************************

typedef struct{
	int len;
	int *notas;
	int *time;
	char *nome;
} musica;

//**************************************

void tone(int freq, int dur){
	int T = 1000000/(2*freq);
	int idx = (dur * freq)/1000;
	for(int i = 0; i <= idx; i++){
		pio_set(PIOB, BUZZ_PIO_IDX_MASK); 
		pio_clear(PIOC,LED1_PIO_IDX_MASK);   
		delay_us(T);                        
		pio_clear(PIOB, BUZZ_PIO_IDX_MASK);
		pio_set(PIOC,LED1_PIO_IDX_MASK); 
		delay_us(T);
	}
}
// CALLBACK
void but_callback(void){
	but_flag = 1;
	delay_ms(200);
};
void but1_callback(void){
	but1_flag = 1;
	delay_ms(200);
	};
void but2_callback(void){
	but2_flag = 1;
	delay_ms(200);
};
void but3_callback(void){
	but3_flag = 1;
	delay_ms(200);
};



// Função de inicialização do uC
void init(void){
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(BUZZ_PIO_ID);
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	pio_configure(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED3_PIO, PIO_OUTPUT_0, LED3_PIO_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED_PIO , PIO_OUTPUT_0, LED_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);
	
	pio_configure(BUT_PIO , PIO_INPUT, BUT_PIO_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT1_PIO, PIO_INPUT, BUT_PIO_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT2_PIO, PIO_INPUT, BUT_PIO_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT3_PIO, PIO_INPUT, BUT_PIO_IDX_MASK, PIO_PULLUP);
	
	
	pio_handler_set(BUT_PIO , BUT_PIO_ID, BUT_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but_callback);	
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but1_callback);	
	pio_handler_set(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but2_callback);	
	pio_handler_set(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but3_callback);	
	
	NVIC_EnableIRQ(BUT_PIO_ID);
	NVIC_SetPriority(BUT_PIO_ID, 4);
	
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4);
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4);
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4);
	
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
}

int main(void) {
	musica pirate;
	pirate.len = sizeof(pirate_notes)/sizeof(pirate_notes[0]);
	pirate.notas = &pirate_notes;
	pirate.nome = &"Pirates";
	pirate.time = &pirate_tempo;

	musica imperial;
	imperial.len = sizeof(imperial_march_notes)/sizeof(imperial_march_notes[0]);
	imperial.notas = &imperial_march_notes;
	imperial.nome = &"Imperial";
	imperial.time = &imperial_march_tempo;

	musica underworld;
	underworld.len = sizeof(underworld_melody)/sizeof(underworld_melody[0]);
	underworld.notas = &underworld_melody;
	underworld.nome = &"Underworld";
	underworld.time = &underworld_tempo;

	musica lista_de_musicas[] = {pirate, imperial, underworld};



	init();
	board_init();
	delay_init();
	gfx_mono_ssd1306_init();


	int i = 0;
	int music_idx = 0;
	pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	while (1) {
		if(pause){
			pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);	
		}
		
		if(but2_flag) {
			pause = !pause;
			but2_flag = 0;	
		}
		if(but1_flag){
			music_idx--;
			if (music_idx<=-1) music_idx = NMUS-1;
			gfx_mono_draw_string("              ", 10,10, &sysfont);
			gfx_mono_draw_string(lista_de_musicas[music_idx].nome, 10,10, &sysfont);
			i=0;
			but1_flag = 0;
		}
		if(but3_flag){
			music_idx++;
			if (music_idx>=NMUS) music_idx = 0;
			gfx_mono_draw_string("               ", 10,10, &sysfont);
			gfx_mono_draw_string(lista_de_musicas[music_idx].nome, 10,10, &sysfont);
			i=0;
			but3_flag = 0;
		}
		
		
		if(!pause){
			if (i>(lista_de_musicas[music_idx].len-1)){
				i = 0;
			}
			int adj = 2;
			int wait = lista_de_musicas[music_idx].time[i] * songspeed/adj;
				
			tone(lista_de_musicas[music_idx].notas[i],lista_de_musicas[music_idx].time[i]/adj);
			delay_ms(wait);
			pio_clear(PIOB, BUZZ_PIO_IDX_MASK);
			delay_ms(wait);
				
			i++;
			
		} 

		
		
	}
	return 0;
}