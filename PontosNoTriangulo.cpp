// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso do Windows, sugere-se a versao 17 do Code::Blocks

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"

#include "Linha.h"

#include "Temporizador.h"
Temporizador T;
double AccumDeltaT=0;

// Variaveis que controlam o triangulo do campo de visao
Poligono PontosDoCenario, CampoDeVisao, TrianguloBase, Envelope, PontosDentro, PontosEnvelope;
float AnguloDoCampoDeVisao=0.0;

// Limites logicos da area de desenho
Ponto Min, Max, Tamanho, Meio;
Ponto PosicaoDoCampoDeVisao, PontoClicado;




bool desenhaEixos = true;
bool desenhaEnvelope = false;
bool desenhaPontosEnvelope = false;
bool desenhaPontos = false;
bool desenhaPontosDentro = false;

bool FoiClicado = false;




// **********************************************************************
// GeraPontos(int qtd)
//      M�todo que gera pontos aleat�rios no intervalo [Min..Max]
// **********************************************************************

void GeraPontos(unsigned long int qtd, Ponto Min, Ponto Max)
{
    time_t t;
    Ponto Escala;
    Escala = (Max - Min) * (1.0/1000.0);
    srand((unsigned) time(&t));
    for (int i = 0;i<qtd; i++)
    {
        float x = rand() % 1000;
        float y = rand() % 1000;
        x = x * Escala.x + Min.x;
        y = y * Escala.y + Min.y;
        PontosDoCenario.insereVertice(Ponto(x,y));
    }
}

// **********************************************************************
// void CriaTrianguloDoCampoDeVisao()
//  Cria um triangulo a partir do vetor (1,0,0), girando este vetor
//  em 45 e -45 graus.
//  Este vetor fica armazenado nas vari�veis "TrianguloBase" e
//  "CampoDeVisao"
// **********************************************************************
void CriaTrianguloDoCampoDeVisao()
{
    Ponto vetor = Ponto(1,0,0);

    TrianguloBase.insereVertice(Ponto(0,0,0));
    CampoDeVisao.insereVertice(Ponto(0,0,0));

    vetor.rotacionaZ(45);
    TrianguloBase.insereVertice(vetor);
    CampoDeVisao.insereVertice(vetor);

    vetor.rotacionaZ(-90);
    TrianguloBase.insereVertice(vetor);
    CampoDeVisao.insereVertice(vetor);

}
// **********************************************************************
// void PosicionaTrianguloDoCampoDeVisao()
//  Posiciona o campo de vis�o na posicao PosicaoDoCampoDeVisao,
//  com a orientacao "AnguloDoCampoDeVisao".
//  O tamanho do campo de vis�o eh de 25% da largura da janela.
// **********************************************************************


void Nodo(){
    vector<Poligono>f[4];
    int nroDePontosNoEnvelope;
    Nodo();
}

long qtdPontostemp = PontosDoCenario.getNVertices();

void quadtree(){
    long qtdPontos = qtdPontostemp;
    if (qtdPontos>6){
        Nodo();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

void envelope(){
    
    Poligono EnvelopeTemp;
    Ponto P1, P2;
    CampoDeVisao.obtemLimites(P1,P2);
    
    Ponto P3 = Ponto (P2.x, P1.y);
    Ponto P4 = Ponto (P1.x, P2.y);
    
    EnvelopeTemp.insereVertice(P3);
    EnvelopeTemp.insereVertice(P2);
    EnvelopeTemp.insereVertice(P4);
    EnvelopeTemp.insereVertice(P1);
    
    Envelope = EnvelopeTemp;
    
    Poligono PontosEnvelopetemp;
    
    for(int i=0; i<PontosDoCenario.getNVertices(); i++){
        if(P3.x > PontosDoCenario.getVertice(i).x &&
           P2.x > PontosDoCenario.getVertice(i).x &&
           P4.x < PontosDoCenario.getVertice(i).x &&
           P1.x < PontosDoCenario.getVertice(i).x &&
           P3.y < PontosDoCenario.getVertice(i).y &&
           P2.y > PontosDoCenario.getVertice(i).y &&
           P1.y < PontosDoCenario.getVertice(i).y &&
           P4.y > PontosDoCenario.getVertice(i).y){
            Ponto P6 = Ponto(PontosDoCenario.getVertice(i).x, PontosDoCenario.getVertice(i).y);
            PontosEnvelopetemp.insereVertice(P6);
        }
        
    }
    PontosEnvelope = PontosEnvelopetemp;
    
    long contador = 0;
    
    Ponto A = CampoDeVisao.getVertice(0);
    Ponto B = CampoDeVisao.getVertice(1);
    Ponto C = CampoDeVisao.getVertice(2);

    Poligono PontosDentrotemp;

    for(int i=0;i<PontosEnvelopetemp.getNVertices(); i++){
        Ponto P = (PontosEnvelopetemp.getVertice(i));
        Ponto V1 = Ponto(B.x-(A.x), B.y-(A.y));
        Ponto V1P = Ponto(P.x-(A.x), P.y-(A.y));
        Ponto V2 = Ponto(C.x-(B.x), C.y-(B.y));
        Ponto V2P = Ponto(P.x-(B.x), P.y-(B.y));
        Ponto V3 = Ponto(A.x-(C.x), A.y-(C.y));
        Ponto V3P = Ponto(P.x-(C.x), P.y-(C.y));
    
        int R1 = V1P.x*V1.y - (V1P.y*V1.x);
        int R2 = V2P.x*V2.y - (V2P.y*V2.x);
        int R3 = V3P.x*V3.y - (V3P.y*V3.x);
    
    
        if ((R1>=0 && R2>=0 && R3>=0) || (R1<0 && R2<0 && R3<0)){
            Ponto P5 = Ponto(PontosEnvelopetemp.getVertice(i).x, PontosEnvelopetemp.getVertice(i).y);
            PontosDentrotemp.insereVertice(P5);
        }
    }
    PontosDentro = PontosDentrotemp;
    contador = PontosDentrotemp.getNVertices();
    cout<<"Número de pontos envelope: "<<contador<<endl;
}

void forcabruta(){
    long contador = 0;
    
    Ponto A = CampoDeVisao.getVertice(0);
    Ponto B = CampoDeVisao.getVertice(1);
    Ponto C = CampoDeVisao.getVertice(2);

    Poligono PontosDentrotemp;

    for(int i=0;i<PontosDoCenario.getNVertices(); i++){
        Ponto P = (PontosDoCenario.getVertice(i));
        Ponto V1 = Ponto(B.x-(A.x), B.y-(A.y));
        Ponto V1P = Ponto(P.x-(A.x), P.y-(A.y));
        Ponto V2 = Ponto(C.x-(B.x), C.y-(B.y));
        Ponto V2P = Ponto(P.x-(B.x), P.y-(B.y));
        Ponto V3 = Ponto(A.x-(C.x), A.y-(C.y));
        Ponto V3P = Ponto(P.x-(C.x), P.y-(C.y));
    
        int R1 = V1P.x*V1.y - (V1P.y*V1.x);
        int R2 = V2P.x*V2.y - (V2P.y*V2.x);
        int R3 = V3P.x*V3.y - (V3P.y*V3.x);
    
    
        if ((R1>=0 && R2>=0 && R3>=0) || (R1<0 && R2<0 && R3<0)){
            Ponto P5 = Ponto(PontosDoCenario.getVertice(i).x, PontosDoCenario.getVertice(i).y);
            PontosDentrotemp.insereVertice(P5);
        }
    }
    PontosDentro = PontosDentrotemp;
    contador = PontosDentrotemp.getNVertices();
    cout<<"Número de pontos Força bruta: "<<contador<<endl;
}



double Ttamanho = 0.2;
int contador;

void DesenhaLinha(Ponto P1, Ponto P2)
{
    glBegin(GL_LINES);
        glVertex3f(P1.x,P1.y,P1.z);
        glVertex3f(P2.x,P2.y,P2.z);
    glEnd();
}





void PosicionaTrianguloDoCampoDeVisao()
{
    float tamanho = Tamanho.x * Ttamanho;
    
    Ponto temp;
    for (int i=0;i<TrianguloBase.getNVertices();i++)
    {
        temp = TrianguloBase.getVertice(i);
        temp.rotacionaZ(AnguloDoCampoDeVisao);
        CampoDeVisao.alteraVertice(i, PosicaoDoCampoDeVisao + temp*tamanho);
    }
    
    if(desenhaPontosEnvelope == true){
        envelope();
        
    }
    
    if(desenhaPontosDentro == true){
        forcabruta();
    }
    
    
    
}
// **********************************************************************
// void AvancaCampoDeVisao(float distancia)
//  Move o campo de vis�o "distancia" unidades pra frente ou pra tras.
// **********************************************************************
void AvancaCampoDeVisao(float distancia)
{
    Ponto vetor = Ponto(1,0,0);
    vetor.rotacionaZ(AnguloDoCampoDeVisao);
    PosicaoDoCampoDeVisao = PosicaoDoCampoDeVisao + vetor * distancia;
}
// **********************************************************************
// void init()
//  Faz as inicializacoes das variaveis de estado da aplicacao
// **********************************************************************
void init()
{
    // Define a cor do fundo da tela (AZUL)
    glClearColor(0, 0,0, 0);

    // Gera ou Carrega os pontos do cenario.
    // Note que o "aspect ratio" dos pontos deve ser o mesmo
    // da janela.

    GeraPontos(10000, Ponto(0,0), Ponto(500,500));

    PontosDoCenario.obtemLimites(Min,Max);
    Min.x--;Min.y--;
    Max.x++;Max.y++;

    Meio = (Max+Min) * 0.5; // Ponto central da janela
    Tamanho = (Max-Min);  // Tamanho da janela em X,Y

    // Ajusta variaveis do triangulo que representa o campo de visao
    PosicaoDoCampoDeVisao = Meio;
    AnguloDoCampoDeVisao = 0;

    // Cria o triangulo que representa o campo de visao
    CriaTrianguloDoCampoDeVisao();
    PosicionaTrianguloDoCampoDeVisao();
}

double nFrames=0;
double TempoTotal=0;
// **********************************************************************
//
// **********************************************************************

void PosicionaCampoDeVisao(int n) {
    switch (n) {
        case 1:
            AnguloDoCampoDeVisao = 0; PosicaoDoCampoDeVisao = Meio; break;
        case 2:
            AnguloDoCampoDeVisao = 90; PosicaoDoCampoDeVisao = Meio; break;
        case 3:
            AnguloDoCampoDeVisao = 90; PosicaoDoCampoDeVisao = Meio*0.5; break;
        case 4:
            AnguloDoCampoDeVisao = 0; PosicaoDoCampoDeVisao = Meio + Meio*0.5;
        break;
        default:
        break;
    }
    PosicionaTrianguloDoCampoDeVisao();
}


void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0/30) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
    
    /*if (TempoTotal > 1)
    {
        cout << "FPS(sem desenho): "<<nFrames/TempoTotal<<endl;
        TempoTotal = 0;
        nFrames = 0;
    }*/
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            0,1);
    
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// **********************************************************************
//
// **********************************************************************


void DesenhaEixos()
{
    glBegin(GL_LINES);
    //  eixo horizontal
        glVertex2f(Min.x,Meio.x);
        glVertex2f(Max.x,Meio.x);
    //  eixo vertical
        glVertex2f(Meio.y,Min.y);
        glVertex2f(Meio.y,Max.y);
    glEnd();
}



// **********************************************************************
//  void display( void )
//
// **********************************************************************
void display( void )
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    glPointSize(1);
    glColor3f(1,1,0); // R, G, B  [0..1]
    PontosDoCenario.desenhaVertices();
    
    glLineWidth(3);
    glColor3f(1,0,0); // R, G, B  [0..1]
    CampoDeVisao.desenhaPoligono();

    if (desenhaEixos)
    {
        glLineWidth(1);
        glColor3f(1,1,1); // R, G, B  [0..1]
        DesenhaEixos();
    }
    
    
    if(desenhaPontosEnvelope)
    {
        if (desenhaEnvelope){
            glLineWidth(2);
            glColor3f(1,1,0);
            Envelope.desenhaPoligono();
        }
        glPointSize(3);
        glColor3f(255,0,132);
        PontosEnvelope.desenhaVertices();
        
        
        glPointSize(3);
        glColor3f(0,1,1);
        PontosDentro.desenhaVertices();
    }
    
    if (desenhaPontosDentro)
    {
        glPointSize(3);
        glColor3f(0,1,1);
        PontosDentro.desenhaVertices();
    }
    
    

    
    
    
    
    
    

    glutSwapBuffers();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard ( unsigned char key, int x, int y )
{

    switch ( key )
    {
        case 27:        // Termina o programa qdo
            exit ( 0 );   // a tecla ESC for pressionada
            break;
        case ' ':
            desenhaEixos = !desenhaEixos;
            break;
        case 'u':
            desenhaEnvelope = !desenhaEnvelope;
            break;
        case 'o':
            desenhaPontosDentro = !desenhaPontosDentro;
            break;
        case 'i':
            desenhaPontosEnvelope = !desenhaPontosEnvelope;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
            int i;
            i = key - '0';
            PosicionaCampoDeVisao(i);
            break;
        default:
            break;
	}
    
    PosicionaTrianguloDoCampoDeVisao();
    glutPostRedisplay();
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
        case GLUT_KEY_LEFT:       // Se pressionar LEFT
            AnguloDoCampoDeVisao+=2;
            break;
        case GLUT_KEY_RIGHT:       // Se pressionar RIGHT
            AnguloDoCampoDeVisao-=2;
            break;
		case GLUT_KEY_UP:
            AvancaCampoDeVisao(2);
            break;
	    case GLUT_KEY_DOWN:
            AvancaCampoDeVisao(-2);
			break;
        case GLUT_KEY_F4:
            Ttamanho = Ttamanho-0.004;
            break;
        case GLUT_KEY_F5:
            Ttamanho = Ttamanho+0.004;
        default:
			break;
	}
    PosicionaTrianguloDoCampoDeVisao();
    glutPostRedisplay();
}



// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int  main ( int argc, char** argv )
{
    cout << "Programa OpenGL" << endl;

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 500, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de titulo da janela.
    glutCreateWindow    ( "Poligonos em OpenGL" );

    // executa algumas inicializa��es
    init ();
    

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc ( display );

    // Define que o tratador de evento para
    // o invalida��o da tela. A funcao "display"
    // ser� chamada automaticamente sempre que a
    // m�quina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc (reshape);

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    
    glutKeyboardFunc (keyboard);

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc (arrow_keys);

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
