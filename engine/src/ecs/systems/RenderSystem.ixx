export module render_system;

export class RenderSystem
{
public:
    void init();
    void update();
    void shutdown();

private:
    struct SDL_Window* window{ nullptr };
    struct SDL_Renderer* renderer{ nullptr };
};
