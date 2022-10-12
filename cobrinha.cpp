#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib> // função srand
#include<ctime> //função rand

using namespace std;
using namespace sf;

#define up 1
#define dw 2
#define lt 3
#define rt 4


int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 16;

    RenderWindow window(sf::VideoMode(800, 600), "JOGO DA COBRINHA", Style::Default, settings);
    window.setFramerateLimit(4);

    //CRIA A COBRINHA
    int tamanho = 4, direcao = rt;
    vector<Vector2f> cobrinha(tamanho);

    cobrinha[0] = Vector2f(4, 1);
    cobrinha[1] = Vector2f(3, 1);
    cobrinha[2] = Vector2f(2, 1);
    cobrinha[3] = Vector2f(1, 1);

    //velocidade
    float fps = 4;
    window.setFramerateLimit(4);

    CircleShape cobra, comida;
    cobra.setFillColor(Color::Blue);
    cobra.setRadius(10);

    comida.setFillColor(Color::Red);
    comida.setRadius(10);

    Vector2f comida_pos;
    comida_pos.x = rand() % 40;
    comida_pos.y = rand() % 30;

    comida.setPosition(Vector2f(comida_pos.x * 20, comida_pos.y * 20));

    bool perdeu = false;
    
    
    while (window.isOpen() && !perdeu)
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Up)
                    direcao = up;
                if (e.key.code == Keyboard::Down)
                    direcao = dw;
                if (e.key.code == Keyboard::Right)
                    direcao = rt;
                if (e.key.code == Keyboard::Left)
                    direcao = lt;
            }

        }

        //Movimento da cobrinha
        for (int i = cobrinha.size() - 1; i > 0; i--)
            cobrinha[i] = cobrinha[i - 1];

        //Movimenta a cabeça da cobrinha para a direção atual
        if (direcao == up)
            cobrinha[0].y--;
        if (direcao == dw)
            cobrinha[0].y++;
        if (direcao == rt)
            cobrinha[0].x++;
        if (direcao == lt)
            cobrinha[0].x--;

        //Ação ao comer
        if (cobrinha[0] == comida_pos)
        {
            cobrinha.push_back(cobrinha[tamanho - 1]);
            tamanho++;
            comida_pos.x = rand() % 40;
            comida_pos.y = rand() % 30;

            comida.setPosition(Vector2f(comida_pos.x * 20, comida_pos.y * 20));

            fps += 0.5;
            window.setFramerateLimit(fps);
            
        }

        // Se a cobrinha sair do limite
        if (cobrinha[0].x < 0 || cobrinha[0].y < 0 || cobrinha[0].x > 40 || cobrinha[0].y >30)
            perdeu = true;

        // Se a cobrinha bater nela mesma
        for (int i=1; i < cobrinha.size(); i++)
            if (cobrinha[i] == cobrinha[0])
            {
                perdeu = true;
                break;
            }

        window.clear();

        window.draw(comida);

        for (int i = 0; i < cobrinha.size(); i++)
        {
            cobra.setPosition(cobrinha[i].x*20, cobrinha[i].y*20);

            int azul, verde;
            azul = (tamanho - i) * (255.f / (float)(tamanho));
            verde = i * (255.f / (float)tamanho);
            cobra.setFillColor(Color(0, verde, azul));

            window.draw(cobra);
        }
        window.display();
    }
    cout << "Você perdeu.\n";
}
