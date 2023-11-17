#include <allegro.h>
#include <locale.h>  

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int ticks;
void tick_counter() { ticks++; }
END_OF_FUNCTION(tick_counter)

volatile int timer;
void incrementa_timer(){timer++;}
END_OF_FUNCTION(incrementa_timer)

volatile int pontos;
void incrementa_pt(){pontos = pontos+100;}// PONTUAÇÃO //
END_OF_FUNCTION(incrementa_pt)
 
void pt2(){pontos = pontos+50;}// PONTUAÇÃO //
END_OF_FUNCTION(incrementa_pt)

enum{ SPLASHSCREEN, GAMEMENU, FASE1, FASE2, FASE3, FASE4, FASE5, FASE6, FASE7, FASE8, FASE9, FASE10, ERROU, ACERTOU, TM_ESG, AJUDA, GAMESCREEN };
int screen_state;

SAMPLE *clique = load_wav("clique.wav");
SAMPLE* erro = load_wav("errou.wav");
SAMPLE* certo = load_wav("certo.wav");


void init()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse();
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  set_window_title("Bio Logicas");

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  ticks = 0;
  LOCK_FUNCTION(tick_counter);
  LOCK_VARIABLE(ticks);
  install_int_ex(tick_counter, BPS_TO_TIMER(60));
  
  pontos = 0;
LOCK_FUNCTION(incrementa_pt); 
LOCK_VARIABLE(pontos);


  screen_state = GAMEMENU;
}



void fase1()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *onca = load_bitmap("onca.bmp",NULL);
    BITMAP *arara = load_bitmap("arara.bmp",NULL);
    BITMAP *canguru = load_bitmap("canguru.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *pau_brasil = load_bitmap("chuva.bmp",NULL);
    BITMAP *veg_fechada = load_bitmap("veg_fechada.bmp",NULL);
    BITMAP *guarana = load_bitmap("guarana.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo3.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1)); //CRONÔMETRO//
    

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}
      
      if(timer>=7){
      if(time>30) time=0;}
      
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 230, 0, makecol(0, 130, 0), -1, "Floresta");
                        textprintf_ex(buffer, font24, 160, 50, makecol(0, 130, 0), -1, "Tropical Pluvial");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(onca, buffer, 0, 0, 50, 130, 640, 480);
                        blit(guarana, buffer, 0, 0, 240, 130, 640, 480);
                        blit(canguru, buffer, 0, 0, 430, 130, 640, 480);
                        blit(pau_brasil, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(arara, buffer, 0, 0, 240, 260, 640, 480);
                        blit(veg_fechada, buffer, 0, 0, 430, 260, 640, 480);
                        if(mouse_b & 1){                              
                                   if(mouse_x>430 && mouse_x<600 && mouse_y>130 && mouse_y<250){
                                                  play_sample(certo, 255, 128, 1000, 0); 
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE2;}
                                   if(mouse_x>50 && mouse_x<415 && mouse_y>130 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                   if(mouse_x>428 && mouse_x<600 && mouse_y>255 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                               
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer);
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(onca);
  destroy_bitmap(arara);
  destroy_bitmap(canguru);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(pau_brasil);
  destroy_bitmap(veg_fechada);
  destroy_bitmap(guarana);
  destroy_bitmap(cursor);
}


void fase2()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *camelo = load_bitmap("camelo.bmp",NULL);
    BITMAP *cacto = load_bitmap("cacto.bmp",NULL);
    BITMAP *vibora = load_bitmap("vibora.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *peixe = load_bitmap("juazeiro.bmp",NULL);
    BITMAP *matinho = load_bitmap("matinho.bmp",NULL);
    BITMAP *rachadura = load_bitmap("rachadura.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo4.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

     if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 240, 10, makecol(0, 130, 0), -1, "Deserto");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(camelo, buffer, 0, 0, 50, 130, 640, 480);
                        blit(cacto, buffer, 0, 0, 240, 130, 640, 480);
                        blit(vibora, buffer, 0, 0, 430, 130, 640, 480);
                        blit(peixe, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(matinho, buffer, 0, 0, 240, 260, 640, 480);
                        blit(rachadura, buffer, 0, 0, 430, 260, 640, 480);
                        if(mouse_b & 1){ 
                                   if(mouse_x>50 && mouse_x<220 && mouse_y>260 && mouse_y<380){
                                                 play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE3;}
                                  if(mouse_x>220 && mouse_x<600 && mouse_y>130 && mouse_y<375){
                                                 exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<220 && mouse_y>130 && mouse_y<260){
                                                exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                         
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(camelo);
  destroy_bitmap(cacto);
  destroy_bitmap(vibora);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(peixe);
  destroy_bitmap(matinho);
  destroy_bitmap(cursor);
}



void fase3()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *panda = load_bitmap("panda.bmp",NULL);
    BITMAP *primavera = load_bitmap("primavera.bmp",NULL);
    BITMAP *lobo = load_bitmap("lobo.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *veado = load_bitmap("veado.bmp",NULL);
    BITMAP *coniferas = load_bitmap("coniferas.bmp",NULL);
    BITMAP *foca = load_bitmap("foca.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo3.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

     if(timer>=7){
      if(time>30) time=0;}     

     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 230, 0, makecol(0, 130, 0), -1, "Floresta");
                        textprintf_ex(buffer, font24, 195, 50, makecol(0, 130, 0), -1, "Temperada");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(veado, buffer, 0, 0, 50, 130, 640, 480);
                        blit(coniferas, buffer, 0, 0, 240, 130, 640, 480);
                        blit(lobo, buffer, 0, 0, 430, 130, 640, 480);
                        blit(primavera, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(panda, buffer, 0, 0, 240, 260, 640, 480);
                        blit(foca, buffer, 0, 0, 430, 260, 640, 480);
                        if(mouse_b & 1){
                                   if(mouse_x>430 && mouse_x<600 && mouse_y>260 && mouse_y<375){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE4;}
                                  if(mouse_x>50 && mouse_x<430 && mouse_y>130 && mouse_y<375){
                                                exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>430 && mouse_x<600 && mouse_y>130 && mouse_y<260){
                                                 exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                              
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(veado);
  destroy_bitmap(panda);
  destroy_bitmap(primavera);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(coniferas);
  destroy_bitmap(foca);
  destroy_bitmap(lobo);
  destroy_bitmap(cursor);
}



void fase4()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *acacia = load_bitmap("acacia.bmp",NULL);
    BITMAP *tucano = load_bitmap("golfinho.bmp",NULL);
    BITMAP *elefante = load_bitmap("elefante.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *zebra = load_bitmap("zebra.bmp",NULL);
    BITMAP *vegetacao = load_bitmap("vegetacao.bmp",NULL);
    BITMAP *girafa = load_bitmap("girafa.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo4.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
      
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 250, 10, makecol(0, 130, 0), -1, "Savana");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(acacia, buffer, 0, 0, 50, 130, 640, 480);
                        blit(zebra, buffer, 0, 0, 240, 130, 640, 480);
                        blit(vegetacao, buffer, 0, 0, 430, 130, 640, 480);
                        blit(elefante, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(tucano, buffer, 0, 0, 240, 260, 640, 480);
                        blit(girafa, buffer, 0, 0, 430, 260, 640, 480);
                        if(mouse_b & 1){
                                   if(mouse_x>240 && mouse_x<410 && mouse_y>260 && mouse_y<380){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE5;}
                                  if(mouse_x>50 && mouse_x<600 && mouse_y>130 && mouse_y<260){
                                                exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<220 && mouse_y>260 && mouse_y<375){
                                                exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>410 && mouse_x<600 && mouse_y>260 && mouse_y<375){
                                                exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                           
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(acacia);
  destroy_bitmap(tucano);
  destroy_bitmap(elefante);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(girafa);
  destroy_bitmap(vegetacao);
  destroy_bitmap(zebra);
  destroy_bitmap(cursor);
}



void fase5()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *alce = load_bitmap("alce.bmp",NULL);
    BITMAP *neve = load_bitmap("neve.bmp",NULL);
    BITMAP *raposa = load_bitmap("raposa.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *esquilo = load_bitmap("esquilo.bmp",NULL);
    BITMAP *coniferas = load_bitmap("coniferas.bmp",NULL);
    BITMAP *zebra = load_bitmap("zebra.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo3.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
    
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 260, 10, makecol(0, 130, 0), -1, "Taiga");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(neve, buffer, 0, 0, 50, 130, 640, 480);
                        blit(raposa, buffer, 0, 0, 240, 130, 640, 480);
                        blit(zebra, buffer, 0, 0, 430, 130, 640, 480);
                        blit(coniferas, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(alce, buffer, 0, 0, 240, 260, 640, 480);
                        blit(esquilo, buffer, 0, 0, 430, 260, 640, 480);
                        if(mouse_b & 1){
                                   if(mouse_x>430 && mouse_x<600 && mouse_y>130 && mouse_y<250){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE6;}
                                  if(mouse_x>50 && mouse_x<415 && mouse_y>130 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>428 && mouse_x<600 && mouse_y>255 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                  
      rest(10);                             
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(neve);
  destroy_bitmap(alce);
  destroy_bitmap(esquilo);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(coniferas);
  destroy_bitmap(zebra);
  destroy_bitmap(raposa);
  destroy_bitmap(cursor);
}



void fase6()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *cavalo = load_bitmap("cavalo.bmp",NULL);
    BITMAP *caranguejo = load_bitmap("caranguejo.bmp",NULL);
    BITMAP *mangue = load_bitmap("mangue.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *mangue2 = load_bitmap("mangue2.bmp",NULL);
    BITMAP *jacare = load_bitmap("jacare.bmp",NULL);
    BITMAP *cobra = load_bitmap("cobra.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo4.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
     if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 210, 10, makecol(0, 130, 0), -1, "Manguezal");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(cavalo, buffer, 0, 0, 50, 130, 640, 480);
                        blit(caranguejo, buffer, 0, 0, 240, 130, 640, 480);
                        blit(mangue, buffer, 0, 0, 430, 130, 640, 480);
                        blit(jacare, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(mangue2, buffer, 0, 0, 240, 260, 640, 480);
                        blit(cobra, buffer, 0, 0, 430, 260, 640, 480);
                         if(mouse_b & 1){
                                   if(mouse_x>50 && mouse_x<220 && mouse_y>130 && mouse_y<250){
                                                 play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE7;}
                                  if(mouse_x>220 && mouse_x<600 && mouse_y>130 && mouse_y<375){
                                                 exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<220 && mouse_y>260 && mouse_y<375){
                                                 exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                              
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZAÇÃO
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(cavalo);
  destroy_bitmap(caranguejo);
  destroy_bitmap(cobra);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(mangue);
  destroy_bitmap(mangue2);
  destroy_bitmap(jacare);
  destroy_bitmap(cursor);
}



void fase7()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *urso = load_bitmap("urso.bmp",NULL);
    BITMAP *vitregia = load_bitmap("vitregia.bmp",NULL);
    BITMAP *arara2 = load_bitmap("arara2.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *capivara = load_bitmap("capivara.bmp",NULL);
    BITMAP *jenipapo = load_bitmap("jenipapo.bmp",NULL);
    BITMAP *tuiuiu = load_bitmap("tuiuiu.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo3.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
     if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 235, 10, makecol(0, 130, 0), -1, "Pantanal");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(urso, buffer, 0, 0, 50, 130, 640, 480);
                        blit(vitregia, buffer, 0, 0, 240, 130, 640, 480);
                        blit(capivara, buffer, 0, 0, 430, 130, 640, 480);
                        blit(tuiuiu, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(jenipapo, buffer, 0, 0, 240, 260, 640, 480);
                        blit(arara2, buffer, 0, 0, 430, 260, 640, 480);
                         if(mouse_b & 1){
                                   if(mouse_x>50 && mouse_x<220 && mouse_y>130 && mouse_y<250){
                                                 play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE8;}
                                  if(mouse_x>220 && mouse_x<600 && mouse_y>130 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<220 && mouse_y>260 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                         
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(urso);
  destroy_bitmap(vitregia);
  destroy_bitmap(capivara);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(tuiuiu);
  destroy_bitmap(arara2);
  destroy_bitmap(jenipapo);
  destroy_bitmap(cursor);
}



void fase8()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *cavalo = load_bitmap("cavalo.bmp",NULL);
    BITMAP *avestruz = load_bitmap("avestruz.bmp",NULL);
    BITMAP *tartaruga = load_bitmap("lobo.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *pradaria = load_bitmap("pradaria.bmp",NULL);
    BITMAP *bufalo = load_bitmap("bufalo.bmp",NULL);
    BITMAP *picapau = load_bitmap("picapau.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo4.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
     if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 225, 10, makecol(0, 130, 0), -1, "Pradarias");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(cavalo, buffer, 0, 0, 50, 130, 640, 480);
                        blit(avestruz, buffer, 0, 0, 240, 130, 640, 480);
                        blit(pradaria, buffer, 0, 0, 430, 130, 640, 480);
                        blit(bufalo, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(picapau, buffer, 0, 0, 240, 260, 640, 480);
                        blit(tartaruga, buffer, 0, 0, 430, 260, 640, 480);
                         if(mouse_b & 1){
                                   if(mouse_x>428 && mouse_x<600 && mouse_y>250 && mouse_y<375){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE9;}
                                  if(mouse_x>50 && mouse_x<415 && mouse_y>130 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>428 && mouse_x<600 && mouse_y>130 && mouse_y<255){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                           
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(cavalo);
  destroy_bitmap(avestruz);
  destroy_bitmap(tartaruga);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(pradaria);
  destroy_bitmap(bufalo);
  destroy_bitmap(picapau);
  destroy_bitmap(cursor);
}


void fase9()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *veg = load_bitmap("veg.bmp",NULL);
    BITMAP *boi = load_bitmap("boi.bmp",NULL);
    BITMAP *urso_polar = load_bitmap("urso_polar.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *avestruz = load_bitmap("avestruz.bmp",NULL);
    BITMAP *rena = load_bitmap("rena.bmp",NULL);
    BITMAP *coruja = load_bitmap("coruja.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo3.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
     if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 250, 10, makecol(0, 130, 0), -1, "Tundra");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(veg, buffer, 0, 0, 50, 130, 640, 480);
                        blit(avestruz, buffer, 0, 0, 240, 130, 640, 480);
                        blit(boi, buffer, 0, 0, 430, 130, 640, 480);
                        blit(urso_polar, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(rena, buffer, 0, 0, 240, 260, 640, 480);
                        blit(coruja, buffer, 0, 0, 430, 260, 640, 480);
                         if(mouse_b & 1){ 
                                   if(mouse_x>240 && mouse_x<410 && mouse_y>130 && mouse_y<260){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = FASE10;}
                                  if(mouse_x>50 && mouse_x<600 && mouse_y>260 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<240 && mouse_y>130 && mouse_y<260){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>410 && mouse_x<600 && mouse_y>130 && mouse_y<260){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                              
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(veg);
  destroy_bitmap(boi);
  destroy_bitmap(urso_polar);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(avestruz);
  destroy_bitmap(rena);
  destroy_bitmap(coruja);
  destroy_bitmap(cursor);
}



void fase10()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *pampa = load_bitmap("veado.bmp",NULL);
    BITMAP *arvore = load_bitmap("tucano.bmp",NULL);
    BITMAP *passaro = load_bitmap("coelho.bmp",NULL);   //IMPLEMNTAÇÃO DAS IMAGENS//
    BITMAP *mico = load_bitmap("alecrim.bmp",NULL);
    BITMAP *jaguatirica = load_bitmap("lagarto.bmp",NULL);
    BITMAP *tamandua = load_bitmap("azinheira.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo4.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT *font24 = load_font("font24.pcx",NULL,NULL);
    
    timer = 0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer, SECS_TO_TIMER(1));  //CRONÔMETRO//

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;
      
      if(timer>=10){
      exit_screen = TRUE;
      screen_state = TM_ESG;}

    if(timer>=7){
      if(time>30) time=0;}     
     
     blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
     if(time<20)
                        textprintf_ex(buffer, font14, 72,20, makecol(255, 0, 0), -1, "%d", timer); 
                        textprintf_ex(buffer, font14, 10, 20, makecol(255, 255, 255), -1, "Tempo: %d", timer);   
                        textprintf_ex(buffer, font24, 240, 10, makecol(0, 130, 0), -1, "Chaparral");   //COISAS PADRÕES DO JOGO//
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                        
                        blit(passaro, buffer, 0, 0, 50, 130, 640, 480);
                        blit(tamandua, buffer, 0, 0, 240, 130, 640, 480);
                        blit(pampa, buffer, 0, 0, 430, 130, 640, 480);
                        blit(jaguatirica, buffer, 0, 0, 50, 260, 640, 480);  //EXIBIÇÃO DAS IMAGENS//
                        blit(arvore, buffer, 0, 0, 240, 260, 640, 480);
                        blit(mico, buffer, 0, 0, 430, 260, 640, 480);
                         if(mouse_b & 1){
                                   if(mouse_x>240 && mouse_x<410 && mouse_y>260 && mouse_y<375){
                                                  play_sample(certo, 255, 128, 1000, 0);
                                                  if(timer<=5){
                                                  incrementa_pt();}
                                                  if(timer>5){
                                                  pt2();}
                                                  exit_screen = TRUE;
                                                  screen_state = ACERTOU;}
                                  if(mouse_x>50 && mouse_x<600 && mouse_y>130 && mouse_y<260){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>50 && mouse_x<240 && mouse_y>260 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}
                                  if(mouse_x>410 && mouse_x<600 && mouse_y>260 && mouse_y<375){
                                                  exit_screen = TRUE;
                                                  screen_state = ERROU;}}
                                                                            
      draw_sprite(buffer, cursor, mouse_x-6, mouse_y);      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font24);
  destroy_bitmap(fundo);
  destroy_bitmap(pampa);
  destroy_bitmap(passaro);
  destroy_bitmap(mico);    //FINALIZAÇÃO DO PROGRAMA//
  destroy_bitmap(jaguatirica);
  destroy_bitmap(tamandua);
  destroy_bitmap(arvore);
  destroy_bitmap(cursor);
}



void gamemenu()
{
  int exit_screen = FALSE;
  int time = 0;

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP* logo = load_bitmap("logo.bmp",NULL);
  FONT* font20 = load_font("font20.pcx",NULL,NULL);

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ENTER]){
        exit_screen = TRUE;
        play_sample(clique, 255, 128, 1000, 0); 
        exit_screen = TRUE;
        screen_state = AJUDA;}
        
      if(key[KEY_ESC])
      fecha_programa();
      
      if(time > 30) time=0;
      
      pontos=0;
      blit(logo, buffer, 0, 0, 0, 0, 640,480);
      if(time < 20)
      textprintf_centre_ex(buffer, font20, SCREEN_W/2, 330, makecol(255, 255, 255), -1, "Press enter to start");
                                  
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
     time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer);
  destroy_bitmap(logo);
  destroy_font(font20);
}


void ajuda()
{
  int exit_screen = FALSE;

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP* fundo = load_bitmap("fundo.bmp",NULL);
  FONT* logo = load_font("fontlogo.pcx",NULL,NULL);
  FONT* font20 = load_font("font20.2.pcx",NULL,NULL);
  FONT *font24 = load_font("font24.pcx",NULL,NULL);
  FONT *fontass = load_font("fontass.pcx",NULL,NULL);

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ESC])
      fecha_programa();
      
      if(key[KEY_ENTER]){
        exit_screen = TRUE;
        play_sample(clique, 255, 128, 1000, 0); 
        screen_state = FASE1;
      }
      
      pontos=0;
      blit(fundo, buffer, 0, 0, 0, 0, 640,480);
      textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
      textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
      
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));

     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer);
  destroy_bitmap(fundo);
  destroy_font(logo);
  destroy_font(font20);
  destroy_font(font24);
  destroy_font(fontass);
}


void acertou(){ 
     int exit_screen = FALSE;
     int time = 0;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fundo = load_bitmap("fundo2.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT* font72 = load_font("font72.pcx",NULL,NULL);

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
     if(key[KEY_ESC])
      fecha_programa();
      
      if(key[KEY_ENTER]){
       exit_screen = TRUE;
       play_sample(clique, 255, 128, 1000, 0); 
      screen_state = GAMEMENU;}
      
      if(time > 30) time=0;

    blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        if(time < 20)
                        textprintf_centre_ex(buffer, font72, SCREEN_W/2, 160, makecol(0, 255, 0), -1, "Acertou!");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                                                                                
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));
      
    time++;
     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font72);
  destroy_bitmap(fundo);
}


void errou()
{
  int exit_screen = FALSE;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fundo = load_bitmap("fundo2.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT* font72 = load_font("font72.pcx",NULL,NULL);

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {      
      if(key[KEY_ENTER]||key[KEY_ESC]){
       exit_screen = TRUE; 
       play_sample(clique, 255, 128, 1000, 0);
      screen_state = GAMEMENU;}
       
    blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_centre_ex(buffer, font72, SCREEN_W/2, 160, makecol(255, 0, 0), -1, "Errou!");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);
                                                                                    
      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));

     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font72);
  destroy_bitmap(fundo);
}


void tm_esg(){
int exit_screen = FALSE;

  ///BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *fundo = load_bitmap("fundo2.bmp",NULL);
    FONT *font14 = load_font("font14.pcx",NULL,NULL);
    FONT *fontass = load_font("fontass.pcx",NULL,NULL);
    FONT* font72 = load_font("font72.pcx",NULL,NULL);

  ///GAME LOOP
  while(!exit_program && !exit_screen)
  {
     while(ticks > 0 && !exit_program && !exit_screen)
     {
      if(key[KEY_ENTER]){
       exit_screen = TRUE;
       play_sample(clique, 255, 128, 1000, 0); 
      screen_state = GAMEMENU;}
      
      if(key[KEY_ESC])
       exit_screen = TRUE;
      screen_state = GAMEMENU;

    blit(fundo, buffer, 0, 0, 0, 0, 640, 480);
                        textprintf_ex(buffer, fontass, 547, 410, makecol(138,43,226),-1,"Bio");
                        textprintf_ex(buffer, fontass, 520, 430, makecol(138,43,226),-1,"Logicas");
                        textprintf_centre_ex(buffer, font72, SCREEN_W/2, 100, makecol(255, 0, 0), -1, "TEMPO");
                        textprintf_centre_ex(buffer, font72, SCREEN_W/2, 210, makecol(255, 0, 0), -1, "ESGOTADO!");
                        textprintf_ex(buffer, font14, 10, 430, makecol(255, 255, 255), -1, "Pontos: %i", pontos);

      draw_sprite(screen, buffer, 0, 0);
      clear_to_color(buffer, makecol(255,255,255));

     ticks--;
     }
  }

  ///FINALIZA?O
  destroy_bitmap(buffer); 
  destroy_font(font14);
  destroy_font(fontass);
  destroy_font(font72);
  destroy_bitmap(fundo);
}



int main()
{
  init();
  SAMPLE *selva = load_wav("selva.wav");
  SAMPLE *aplausos = load_wav("aplausos.wav");
  SAMPLE *menu = load_wav("menu.wav");
  SAMPLE *fases = load_wav("fases.wav");

  while(!exit_program)
  {
     if(screen_state == FASE1){ 
     play_sample (fases, 150, 128, 1000, 1);
     fase1();}     

     if(screen_state == GAMEMENU){
     stop_sample(fases);
     stop_sample(aplausos);
     stop_sample(erro);
     stop_sample(clique);
     play_sample (selva, 150, 128, 1000, 1);
     play_sample(menu, 255, 128, 1000, 1);
     gamemenu();}
       
     if(screen_state == FASE2){
       fase2();}
     
     if(screen_state == FASE3){
       fase3();}
       
     if(screen_state == FASE4){
       fase4();}
     
     if(screen_state == FASE5){
       fase5();}
     if(screen_state == FASE6){
       fase6();}
       
     if(screen_state == FASE7){
       fase7();}
       
     if(screen_state == FASE8){
       fase8();}
       
     if(screen_state == FASE9){
       fase9();}
       
     if(screen_state == FASE10){
       fase10();}
       
     if(screen_state == ERROU){
     stop_sample(fases);
     play_sample(erro, 255, 128, 1000, 0);
       errou();}
       
     if(screen_state == ACERTOU){
     stop_sample(selva);
     play_sample (aplausos, 255, 128, 1000, 0);
       acertou();}
       
     if(screen_state == TM_ESG){
     stop_sample(fases);
       tm_esg();}
       
     if(screen_state == AJUDA){
     stop_sample(menu);
     stop_sample(selva);
       ajuda();}
  }

  return 0;
}
END_OF_MAIN();
