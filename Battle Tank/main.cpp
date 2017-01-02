#include <allegro.h>
// Definimos qual é o número máximo de tiros simultâneos

BITMAP* buffer;
BITMAP* face;
BITMAP* face2;
SAMPLE *musica = load_sample("tiro.wav");
SAMPLE *fundo = load_sample("fundo.wav");

int flag_tiro,flag_tiro2,vida = 5,vida2 = 5;
int vidas = 5,vidas2 = 5;

///MÉTODO DE CAIXAS DE COLISÃO
int colisao(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if( (x1 > x2 + w2) || (y1 > y2 + h2) || (x2 > x1 + w1) || (y2 > y1 + h1) )
     return FALSE;
    else
     return TRUE;
}
//Struct do tank
struct Tank
{
	//As coordenadas do tank
	int x, y;
	//Velocidade do tank
	int vel;
	//Bitmap com a imagem do tank
	BITMAP *img_direita;
    BITMAP *img_esquerda;
    BITMAP *img_cima;
    BITMAP *img_baixo;
}Tank1,Tank2;

// A Struct do tiro
struct Tiro
{
	// Coordenadas
	int x, y;
	// Velocidade
	int vel;
	// O Tiro está ativo?
	int ativo;

	int logicaInvertida;

	// BITMAP do tiro
    BITMAP *img_tiro;

}tiro[500],tiro2[500];

void iniciar_programa(){
    //inicialização
    allegro_init();
    install_timer();
    install_keyboard();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
    set_window_title("Battle Tank");

    buffer = create_bitmap(800,600);
    face = load_bitmap("img/tankR.bmp",NULL);
    face2 = load_bitmap("img/inimigoL.bmp",NULL);

     play_sample(fundo,255,150,1000,0);

}

void iniciar_tanks(){

     Tank1.x = 60;
     Tank1.y = 558;
     Tank1.vel = 4;
     Tank1.img_esquerda = load_bitmap("img/tankL.bmp",NULL);
     Tank1.img_direita = load_bitmap("img/tankR.bmp",NULL);
     Tank1.img_cima = load_bitmap("img/tankU.bmp",NULL);
     Tank1.img_baixo = load_bitmap("img/tankD.bmp",NULL);

     //Tank DOIS
     Tank2.x = 695;
     Tank2.y = 558;
     Tank2.vel = 4;
     Tank2.img_esquerda = load_bitmap("img/inimigoL.bmp",NULL);
     Tank2.img_direita = load_bitmap("img/inimigoR.bmp",NULL);
     Tank2.img_cima = load_bitmap("img/inimigoU.bmp",NULL);
     Tank2.img_baixo = load_bitmap("img/inimigoD.bmp",NULL);

}

void iniciar_tiros(){
    ///criando os tiros...
    int i;
	for (i = 0; i < 500; i++)
	{
		tiro[i].ativo = 0;
		tiro2[i].ativo = 0;

		tiro[i].vel = 8;
		tiro2[i].vel = 8;

		tiro[i].logicaInvertida = 0;
		tiro2[i].logicaInvertida = 1;

    	tiro[i].img_tiro = load_bitmap("img/tiro1.bmp",NULL);
        tiro2[i].img_tiro = load_bitmap("img/tiro2.bmp",NULL);
	}
	flag_tiro = 0;
	flag_tiro2 = 0;
}
void atirar(int tank, int logicaInvertida)
{
	///Temos que percorrer o array até achar um tiro que não está ativo, assim:
	int i;
	for (i = 0; i < 500; i++)
	{

        if (tank == 1){
    		if (tiro[i].ativo == 0)
    		{


                tiro[i].ativo = 1;
                play_sample(musica,255,150,1000,FALSE);
    			if (logicaInvertida == 0){

                ///definindo onde sai os tiros player1
        			tiro[i].x = Tank1.x + 11;
        			tiro[i].y = Tank1.y + 8;
                }
                else{
                	tiro[i].x = Tank1.x + 11;
                	tiro[i].y = Tank1.y + 8;
                }
    			tiro[i].logicaInvertida = logicaInvertida;
    			break;


    		}
        }
	    else{
             if (tiro2[i].ativo == 0)
    		{
                ///definindo onde sai os tiros player2
                tiro2[i].ativo = 1;
                play_sample(musica,255,150,1000,FALSE);
    			if (logicaInvertida == 0){


        			tiro2[i].x = Tank2.x + 11;
        			tiro2[i].y = Tank2.y + 8;
                }
                else{
                	tiro2[i].x = Tank2.x + 11;
                	tiro2[i].y = Tank2.y + 8;
                }
    			tiro2[i].logicaInvertida = logicaInvertida;
    			break;

    		}
        }


	}
}
void show_tiros(int tank)
{
//Essa função não só mostra os tiros na tela, como os atualiza.
//Vai mudando sua posição e verifica se ele sai da tela (desativa-o).

	int i;
	for (i = 0; i < 50; i++)
	{

        if (tank == 1){

            if (tiro[i].ativo == 1)
    		{
    			draw_sprite(buffer, tiro[i].img_tiro, tiro[i].x, tiro[i].y);

    			if (tiro[i].logicaInvertida == 0){
                    if (tiro[i].x < buffer->w)
        			{
        			    ///definindo a direnção do tiro /\ <- ->
        				tiro[i].x += tiro[i].vel;
        			}
        			else
        			{
        				tiro[i].ativo = 0;
        			}
                }
    			if (tiro[i].logicaInvertida == 1){
                     if (tiro[i].x >= 1)
        			{
        				tiro[i].x -= tiro[i].vel;
        			}
        			else
        			{
        				tiro[i].ativo = 0;
        			}
                }
                if (tiro[i].logicaInvertida == 2){
                     if (tiro[i].y >= 1)
        			{
        				tiro[i].y -= tiro[i].vel;
        			}
        			else
        			{
        				tiro[i].ativo = 0;
        			}
                }

                if (tiro[i].logicaInvertida == 3){
                     if (tiro[i].y >= 1)
        			{
        				tiro[i].y += tiro[i].vel;
        			}
        			else
        			{
        				tiro[i].ativo = 0;
        			}
                }

    		}
    		if (tiro[i].ativo == 1){
                    ///checando a colisao entre o tiro e o tank
                  if(colisao(tiro[i].x, tiro[i].y,tiro[i].img_tiro->w, tiro[i].img_tiro->h,Tank2.x,Tank2.y, Tank2.img_direita->w, Tank2.img_direita->h) == TRUE){
                     tiro[i].ativo = 0;
                     vidas2 -= 1;
                   }
             }
        }
        else
        {
    	if (tiro2[i].ativo == 1)
    		{
    			draw_sprite(buffer, tiro2[i].img_tiro, tiro2[i].x, tiro2[i].y);
                ///msm coisa só que para o player2
    			if (tiro2[i].logicaInvertida == 0){
                    if (tiro2[i].x < buffer->w)
        			{
        				tiro2[i].x += tiro2[i].vel;
        			}
        			else
        			{
        				tiro2[i].ativo = 0;
        			}
                }
    			if (tiro2[i].logicaInvertida == 1){
                     if (tiro2[i].x >= 1)
        			{
        				tiro2[i].x -= tiro2[i].vel;
        			}
        			else
        			{
        				tiro2[i].ativo = 0;
        			}
                }
                if (tiro2[i].logicaInvertida == 2){
                     if (tiro2[i].y >= 1)
        			{
        				tiro2[i].y -= tiro2[i].vel;
        			}
        			else
        			{
        				tiro2[i].ativo = 0;
        			}
                }
                if (tiro2[i].logicaInvertida == 3){
                     if (tiro2[i].y >= 1)
        			{
        				tiro2[i].y += tiro2[i].vel;
        			}
        			else
        			{
        				tiro2[i].ativo = 0;
        			}
                }


    		}
    		if ( tiro2[i].ativo == 1){
                  if(colisao(tiro2[i].x, tiro2[i].y,tiro2[i].img_tiro->w, tiro2[i].img_tiro->h,Tank1.x,Tank1.y, Tank1.img_direita->w, Tank1.img_direita->h) == TRUE){
                      tiro2[i].ativo = 0;
                      vidas -= 1;
                   }
             }
    	}

        ///colisao entre as balas :O
	if(colisao(tiro[i].x, tiro[i].y,tiro[i].img_tiro->w, tiro[i].img_tiro->h,tiro2[i].x, tiro2[i].y,tiro2[i].img_tiro->w, tiro2[i].img_tiro->h) == TRUE){
         if ((tiro[i].ativo == 1)&& (tiro2[i].ativo == 1)){
         tiro[i].ativo = 0;
         tiro2[i].ativo = 0;
         }
      }

    }

}



int main()
{
    iniciar_programa();
    iniciar_tanks();
    iniciar_tiros();

    // variaveis
    int x = 1, y = 480,i,logicaInvertida = 0,logicaInvertida1 = 1;
    int limite = 480,limite2 = 480, teclabaixo = 0,teclabaixo2 = 0;


    // Loop infinito
while((!key[KEY_ESC]) and ((vidas >=0) && (vidas2 >= 0))){
        ///exibindo na tela ambas vidas
      textprintf_ex(screen, font, 10, 588, makecol(255, 0, 0),-1, "%d Vidas - Player 1", vidas);
      textprintf_right_ex ( screen , font , SCREEN_W - 10, 588,makecol (255, 0, 0), -1,"Player 2 - Vidas %d", vidas2);

      rest(30);


    ///MOVIMENTAÇÃO:
      if(key[KEY_D])
      {
            Tank1.x = Tank1.x + Tank1.vel;
            face = Tank1.img_direita;
            if (Tank1.x >=760)Tank1.x = 760;
            logicaInvertida = 0;
      }
      if(key[KEY_A])
      {
             Tank1.x = Tank1.x - Tank1.vel;
             face = Tank1.img_esquerda;
             if (Tank1.x <=10)Tank1.x = 10;
            logicaInvertida = 1;

      }
      if(key[KEY_W]) {

         Tank1.y = Tank1.y - Tank1.vel;
         face = Tank1.img_cima;
         if (Tank1.y <=16)Tank1.y = 16;
         logicaInvertida = 2;
      }
      if(key[KEY_S]) {
        Tank1.y = Tank1.y + Tank1.vel;
        face = Tank1.img_baixo;
        if (Tank1.y >=558)Tank1.y = 558;
        logicaInvertida = 3;

      }

      if(key[KEY_RIGHT]) {
         Tank2.x = Tank2.x + Tank2.vel;
         face2 = Tank2.img_direita;
         if (Tank2.x >=760)Tank2.x = 760;
         logicaInvertida1 = 0;
      }
      if(key[KEY_LEFT]) {
         Tank2.x = Tank2.x - Tank2.vel;
         face2 = Tank2.img_esquerda;
         if (Tank2.x <=10)Tank2.x = 10;
         logicaInvertida1 = 1;
         }

      if(key[KEY_UP]) {

         Tank2.y = Tank2.y - Tank2.vel;
          face2 = Tank2.img_cima;
          if (Tank2.y <=16)Tank2.y = 16;
          logicaInvertida1 = 2;
      }

      if(key[KEY_DOWN]) {
            Tank2.y = Tank2.y + Tank2.vel;
            face2 = Tank2.img_baixo;
            if (Tank2.y >=558)Tank2.y = 558;
            logicaInvertida1 = 3;
      }


    if (vidas <=0){
    // Fim do jogo pro 1
    }
    if (vidas2 <= 0){
    // fim do jogo pro 2
    }

       draw_sprite(buffer,face,Tank1.x,Tank1.y);
       draw_sprite(buffer,face2,Tank2.x,Tank2.y);

       if(key[KEY_F])
       {
		if (flag_tiro == 0){

            flag_tiro = 1;
			atirar(1,logicaInvertida);

        }
        }

      else
	{
		flag_tiro = 0;
	}
       if(key[KEY_SPACE])
       {
          if (flag_tiro2 == 0){

            flag_tiro2 = 1;
			atirar(2,logicaInvertida1);

        }

       }
       else {
         flag_tiro2 = 0;
       }

       show_tiros(1);
       show_tiros(2);
       draw_sprite(screen,buffer,0,0);

       clear(buffer);


}
BITMAP *venceu1 = load_bitmap("img/venceu1.bmp",NULL);
BITMAP *venceu2 = load_bitmap("img/venceu2.bmp",NULL);


if ((vidas <= 0) || (vidas2 <= 0)){
SAMPLE *gameover = load_sample("gameover.wav");
play_sample(gameover,255,150,1000,0);
  while (!key[KEY_ESC]){

        if (vidas2 < 0){
            draw_sprite(buffer,venceu1,0,0);
            draw_sprite(screen,buffer,0,0);


        }
        if (vidas < 0){
            draw_sprite(buffer,venceu2,0,0);
            draw_sprite(screen,buffer,0,0);
        }

  }
}

    ///DESTROY
    destroy_bitmap(buffer);
    destroy_bitmap(Tank1.img_esquerda);
    destroy_bitmap(Tank1.img_direita);
    destroy_bitmap(Tank1.img_baixo);
    destroy_bitmap(Tank1.img_cima);
    destroy_bitmap(Tank2.img_esquerda);
    destroy_bitmap(Tank2.img_direita);
    destroy_bitmap(Tank2.img_baixo);
    destroy_bitmap(Tank2.img_cima);
    destroy_bitmap(face);
    destroy_bitmap(face2);
    destroy_bitmap(venceu1);
    destroy_bitmap(venceu2);
    destroy_sample(musica);
    destroy_sample(fundo);

    for (i = 0; i < 10; i++){
        destroy_bitmap(tiro[i].img_tiro);
        destroy_bitmap(tiro2[i].img_tiro);
    }
    return(0);

}
END_OF_MAIN();

