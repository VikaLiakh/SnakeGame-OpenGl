
#include <stdlib.h>
#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <iostream> 

int N = 30, M = 20; // змія буде ходити по квадратикам, розміри квадратів стосовно  нашого вікна
int scale = 25; // размір квадрата. коли OpenGL буде розкреслювати поле для гри, відстань між гранями квадрата буде 25 пікселів

int w = scale * N; // ширина поля  
int h = scale * M; // висота поля

int dir, num = 4; // 4 напрямок і початковий розмір змії.
//struct { int x; int y; } s[100]; // структура змії, X и Y координати, массив с з довжиною.

class fruct // класс фрукти,  які буде їсти наша зміяя
{
public:
    int x, y; 
    
    void New() {
        x = rand() % N;
        y = rand() % M; 
    }

    void DrawFruct() 
    {
        glColor3f(0.0, 1.0, 1.0);  
        glRectf(x * scale, y * scale, (x + 1) * scale, (y + 1) * scale); 
    }
} m[5]; 

class Snakes {

public:
    struct { int x; int y; };
    void Snake()
    {
        glColor3f(0.1, 1.0, 0.0);
        for (int i = 0; i < num; i++)
        {
            glRectf(s[i].x * scale, s[i].y * scale, (s[i].x + 0.9) * scale, (s[i].y + 0.9) * scale);
        }
    }
} s[100];

void Draw() // ф-ція, яка малює лінії
{
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINES); 
    for (int i = 0; i < w; i += scale) 
    {
        glVertex2f(i, 0); glVertex2f(i, h); 
    }
    for (int j = 0; j < h; j += scale) 
    {
        glVertex2f(0, j); glVertex2f(w, j); 
    }

    glEnd(); 
}

void tick() 
{
    for (int i = num; i > 0; --i) // рух змії.
    {
        s[i].x = s[i - 1].x; 
        s[i].y = s[i - 1].y; 
    }
    // управління зміюкою.
    if (dir == 0) s[0].y += 1; 
    if (dir == 1) s[0].x -= 1; 
    if (dir == 2) s[0].x += 1; 
    if (dir == 3) s[0].y -= 1; 

    for (int i = 0; i < 10; i++) //зміюка росте
    {
        if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) 
        {
            num++; 
            m[i].New(); 
        }
    }
    // для того щоб змія не виходила за рамки поля
    if (s[0].x > N) dir = 1; //  протилежний напрямок
    if (s[0].y > M) dir = 3; 
    if (s[0].x < 0) dir = 2;
    if (s[0].y < 0) dir = 0;

    for (int i = 1; i < num; i++) 
        if (s[0].x == s[i].x && s[0].y == s[i].y) // перевіряємо кординати частинок змії, якщо X и Y координата головної частини рівна координаті любої
            num = i; // другий блок зміюки ,задаємо їй довжину а та частина пропадає .
}



void Key(int key, int a, int b) 
{
    switch (key) 
    {
    case 101: dir = 0; break; 
    case 102: dir = 2; break;
    case 100: dir = 1; break;
    case 103: dir = 3; break;
    }
}

void Display() 
{
    glClear(GL_COLOR_BUFFER_BIT); 

    Draw(); 
    for(int i=0;i<100;i++)
         s[i].Snake(); 

    for (int i = 0; i < 5; i++) 
        m[i].DrawFruct();

    glFlush(); 
    glutSwapBuffers();
}

void timer(int = 0) 
{
    Display();  
    tick();
    glutTimerFunc(200, timer, 0);  
}

int main(int argc, char** argv) 
{
    std::cout << "Zmiyuka Zlyuka :P\n Loading..."; 
    srand(time(0));
    for (int i = 0; i < 10; i++) 
        m[i].New();

    s[0].x = 10; 
    s[0].y = 10; 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h); 
    glutCreateWindow("Game"); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Display); 
    glutSpecialFunc(Key);
    glutTimerFunc(50, timer, 0); 
    glutMainLoop();

    return 0;
}