////////// graph2d ///////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "graph2d.h"

using namespace graph;

////////// class pollEvent ///////////////////////////////////////////////////
// Описание : graph2d.h                                                     //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
PollEvent::PollEvent()
{
    window_ = nullptr;
}

// (4) Первичная инициализация обработчика, установление связей
void PollEvent::initialize(Window& window)
{
    window_ = &window;
}

// (5) Обрабатывает нажатия клавиш и состояние окна программы
void PollEvent::checkEvents()
{
    // Упрощаем имя, выставляем базовые значения
    Status& status = window_->status;
    
    // Опустошаем очередь событий окна
    while (window_->window.pollEvent(event_))
    {
        switch (event_.type)
        {
            // События окна
            case sf::Event::Closed :
                status.window.closed = true;
                break;
            
            case sf::Event::Resized :
                status.window.resized = true;
                break;
            
            // События клавиатуры
            case sf::Event::KeyReleased :
                keyRefresh(false);
                break;
            
            case sf::Event::KeyPressed :
                keyRefresh(true);
                break;
            
            // События мыши
            case sf::Event::MouseButtonReleased :
                mouseButtonRefresh(false);
                break;
            
            case sf::Event::MouseButtonPressed :
                mouseButtonRefresh(true);
                break;
            
            case sf::Event::MouseMoved :
                status.mouse.x = event_.mouseMove.x;
                status.mouse.y = event_.mouseMove.y;
                break;
            
            case sf::Event::MouseEntered :
                status.mouse.inside = true;
                break;
            
            case sf::Event::MouseLeft :
                status.mouse.inside = false;
                break;
            
            default :
                status.window.closed = false;
                status.window.resized = false;
                break;
        }
    }
}

////////// private ///////////////////////////////////////////////////////////

// (1) Обновляет значение соответствующей переменной клавиши
void PollEvent::keyRefresh(bool isPressed)
{
    // Упрощаем имя
    Status& status = window_->status;
    
    // Выбираем нужную клавишу
    switch (event_.key.code)
    {
        case sf::Keyboard::Num1 :
            status.key.num1 = isPressed;
            break;
        
        case sf::Keyboard::Num2 :
            status.key.num2 = isPressed;
            break;
        
        case sf::Keyboard::Num3 :
            status.key.num3 = isPressed;
            break;
        
        case sf::Keyboard::Space :
            status.key.space = isPressed;
            break;
        
        default :
            break;
    }
}

// (2) Обновляет значение соответствующей переменной кнопки мыши
void PollEvent::mouseButtonRefresh(bool isPressed)
{
    // Упрощаем имя
    Status& status = window_->status;
    
    // Выбираем нужную кнопку мыши
    switch (event_.mouseButton.button)
    {
        case sf::Mouse::Button::Left :
            status.mouse.lButton = isPressed;
            break;
        
        case sf::Mouse::Button::Right :
            status.mouse.rButton = isPressed;
            break;
        
        default :
            break;
    }
    
    // Обновляем координаты мыши
    status.mouse.x = event_.mouseButton.x;
    status.mouse.y = event_.mouseButton.y;
}

////////// class TestGraph ///////////////////////////////////////////////////
// Описание : graph2d.h                                                     //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
TestGraph::TestGraph()
{
    window_ = nullptr;
}

// (4) Первичная инициализация обработчика, установление связей
void TestGraph::initialize(int sizeX, int sizeY, Window& window)
{
    window_ = &window;
    image_.create(sizeX, sizeY, sf::Color(0, 0, 0));
    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
    window_->window.clear(sf::Color(0, 200, 0));
    window_->window.draw(sprite_);
    window_->window.display();
}

// (5) Обрабатывает нажатия клавиш и состояние окна программы
void TestGraph::draw()
{
    if (checkMouse() || window_->status.window.resized)
    {
        texture_.update(image_);
        window_->window.clear(sf::Color(0, 200, 0));
        window_->window.draw(sprite_);
        window_->window.display();
    }
}

////////// private ///////////////////////////////////////////////////////////

// (1) Изменяет цвет пикселя картинки в соотв. с сост. мыши
bool TestGraph::checkMouse()
{
    // Упрощаем имя
    Status& status = window_->status;
    
    // Размеры изображения
    int sizeX = image_.getSize().x;
    int sizeY = image_.getSize().y;
    
    // Закрашиваем нужным цветом пиксели при нажатии кнопок мышы
    if (status.mouse.lButton)
    {
        int x = status.mouse.x;
        int y = status.mouse.y;
        
        // Если внутри спрайта, то меняем цвет
        if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
        {
            image_.setPixel(x, y, sf::Color(255, 255, 255));
            return true;
        }
        return false;
    }
    else
    if (status.mouse.rButton)
    {
        int x = status.mouse.x;
        int y = status.mouse.y;
        
        // Если внутри спрайта, то меняем цвет
        if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
        {
            image_.setPixel(x, y, sf::Color(0, 255, 255));
            return true;
        }
        return false;
    }
    return false;
}