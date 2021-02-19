# CG-2021

Computer Graphics course at CMC MSU in 2021

# Problem desctiption

## Rogue-like с лабиринтом из комнат (на подобие Hades, Binding of Isaac, подземелий в Legend of Zelda: A link to the past etc.)

Игроку необходимо выбраться из лабиринта, состоящего из соединенных между собой квадратных/ прямоугольных комнат нескольких разных типов. Из очередной комнаты игроку доступно от 1 до 4 выходов (по одному возможному выходу в каждой из стен).

**Обязательными элементами задания являются:**

- Чтение карты общего лабиринта и карты комнат разных типов из текстовых файлов. Лабиринт состоит минимум из 20 комнат 4 разных типов. Одна комната целиком помещается на экран.
- Каждый символ в текстовом файле общего лабиринта задаёт один из нескольких типов комнат - ‘A’, ‘B’, ‘C’, ...:
- Каждый символ в текстовом файле для комнаты задает один из нескольких вариантов тайла:
  - пустое пространство: ‘ ‘ (пробел)
  - стена: ‘#’
  - пол: ‘.’
  - игрок: ‘@’
  - выход из комнаты: ‘x’
  - выход из всего лабиринта: ‘Q’
  - ключи, которые позволяют открывать закрытые выходы из комнат: ‘K’
- Визуализация карты при помощи графики с обязательным отображением всех игровых элементов разными изображениями (тайлами/спрайтами). 
- Реализация движения и взаимодействия с окружения игрока при помощи управления с клавиатуры (например, W, A, S, D, пробел). Игрок не должен проходить сквозь стены.
- При попадании в пустоту/ловушку игрок должен умирать: с помощью графики необходимо вывести сообщение о проигрыше и завершить игру.
- Если игрок достиг выхода из лабиринта, необходимо при помощи графики вывести сообщение об успешном окончании игры.

**Дополнительная часть (максимум - 15 баллов)**

- Реализовать врагов, которые перемещаются по лабиринту (вариант А) или по комнате (вариант Б) - патрулируют по маршруту (2 балл) и/или двигаются на игрока (4 балла).
- Более продвинутые реализации врагов: до 4 баллов. Например, противники атакуют с некоторой дистанции и отбегают от игрока, при его приближении.  
- Анимация статических объектов - например, сокровища и шипы ловушек блестят. (2 балла)
- Плавная спрайтовая анимация динамических объектов - походка игрока и врагов, открытие дверей и.т.д. (от 2 до 5 баллов)
- Реализовать графический эффект перехода между уровнями (вариант А) и комнатами (вариант Б) - постепенное “угасание” и появление игровой карты (fade out / fade in), эффект “мозаики”, плавное “перетекание” одного изображения в другое и т.п. (3 балла)
- Эффекты пост-обработки всего изображения - “дрожание” воздуха (heat haze), размытие/туман и т.п. (3 балла)
Источники света - факелы, лампы и т.д., которые “освещают” (=изменяют цвет) соседних тайлов в некотором радиусе. (4 балла)
  - анимация источников света (+1 балл)
  - bloom (+4 балла)
- Реализация и графическое отображение инвентаря (3 балла)
- Графическое отображение характеристик игрока и соответствующие им игровые механики - например, если выводится здоровье, то игрок может его потерять (ловушки, враги) и, возможно, восстановить. (2 балла)
- Механика ближнего боя с анимацией. (2 балла)
- Механика дальнего боя (стрелковое оружие и/или магия - огненные шары, волшебные стрелы и т.д.) с анимацией летящего снаряда. (от 3 до 6 баллов в зависимости от субъективно оцениваемого визуального качества и сложности)
Визуальные эффекты боя - “вылетающие” спрайты цифр повреждений, искры, “тряска” экрана и т.п. (от 2 до 4 баллов)
- Финальный босс игры: от 2 до 6 баллов. Боссы, отличающиеся от обычных врагов только числовыми параметрами(жизни, урон и тд.), оцениваются в 2 балла. Чтобы получить больше необходимо реализовать хотя бы одну оригинальную механику для босса. Этой механики не должно быть ни у одного другого противника. 
- Реализация большого лабиринта (вариант А): 5 баллов. В данном пункте предполагается, что карта уровня больше чем отображаемая в окне область. Необходимо реализовать отображение видимой области, которая располагается вокруг игрока и перемещается вместе с ним.

# Project structure

glad.c
Image.cpp
Player.cpp
main.cpp