#include "bazooka.hpp"
#include "resource.hpp"

int main()
{
    CBazooka bazooka(BAZOOKA_MP3, sizeof(BAZOOKA_MP3));
    bazooka.Sleep(400);
    bazooka.Text("Kablow");
    bazooka.Sleep(1200);
    bazooka.Text("Kaboom");
    bazooka.Sleep(2100);
    bazooka.Text("Rest in peace my granny");
    bazooka.Text("She got hit by a bazooka");
    bazooka.Sleep(550);
    bazooka.Text("Yeah I think about it");
    bazooka.Text("Every time I hit the hookah");
    bazooka.Sleep(1200);
    bazooka.Text("Kaboom");
    bazooka.Sleep(1200);
    bazooka.Text("Kablow");
    bazooka.Sleep(1200);
    bazooka.Text("Kaboom");

    bazooka.Play();
    return 0;
}