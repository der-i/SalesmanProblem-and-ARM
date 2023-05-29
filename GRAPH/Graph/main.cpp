#include "header.h"





int main()
{
	system("chcp 1251 >> null");
	
	bool upravlenie = true, dejkstra = false, salesman = false, close = false;
	list<int> lst;

	graph<string> gr;
	//gr.addVertex("���");	//0
	//gr.addVertex("12.2");	//1
	//gr.addVertex("13.3");	//2
	//gr.addVertex("14.4");	//3
	//gr.addVertex("15.5");	//4
	//gr.addVertex("17.7");	//5
	//gr.addVertex("10.01");	//6
	//gr.addEdge("12.2", "13.3", 23);
	//gr.addDirectEdge("17.7", "13.3", 1);
	//gr.addDirectEdge("14.4", "17.7", 2);
	//gr.addDirectEdge("10.01","���", 23);
	//gr.addEdge("���", "14.4", 25);
	//gr.addEdge("10.01", "14.4", 23);
	//gr.addDirectEdge("15.5", "12.2", 13);
	//gr.addEdge("12.2", "17.7", 35);
	//gr.addEdge("10.01", "13.3", 25);
	//gr.addEdge("10.01", "12.2", 12);
	//gr.addEdge("12.2", "14.4", 12);
	//gr.addEdge("14.4", "13.3", 1);
	//gr.addEdge("14.4", "15.5", 53);
	//gr.addEdge("17.7", "15.5", 42);
	//gr.addEdge("17.7", "10.01", 15);

	//gr.BFSHelper("12.2");
	//cout << endl << endl;
	//gr.DFSHelper("12.2");

	//�������� ������� ��� ��������� ������� � ���������� ��� ������������
	vector<sf::CircleShape> v(gr.size());	//�������� ������� ��� ��������� ������
	vector<sf::RectangleShape> v_edges;		//�������� ������� ��� ��������� �����
	vector<sf::Text> v_text;				//�������� ������� ��� ��������� ������
	vector<sf::Text> v_weight;				//�������� ������� ��� ��������� ���� �����
	vector<sf::Text> v_dejkstra;			//�������� ������� ��� ��������� ������ ��������� ��������
	
	vector<int> for_dejk;
	//�������� ������ ��� ������ ������
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2);

	//�������� ������ ��� ���� �����
	sf::Font font_weight;
	font_weight.loadFromFile("arial.ttf");
	sf::Text text_weight;
	text_weight.setFont(font_weight);
	text_weight.setCharacterSize(18);
	text_weight.setFillColor(sf::Color::Black);
	text_weight.setStyle(sf::Text::Bold);
	text_weight.setOutlineColor(sf::Color::White);
	text_weight.setOutlineThickness(4);

	vector<sf::ConvexShape> v_direction;
	//����� �������, ��� ���������� ������� ����������
	cordCalculate(v, gr.size());	//�������, ������� ��������� ������ ������������ ������
	gr.calcCordEdge(v_edges, v_direction,v);	//�����, ������� ��������� ������ ��������� ��� �����
	gr.calcCordText(v_text, v, text);	//������, ������������� ���������� ��� ������� �������
	gr.calcCordWeight(v_weight, v, text_weight);	//�����, �������������� ���������� ��� ���� �����
	
	size_t temp_size = gr.size();	//����������, ������� �������� �� ���������� ������������ ����� � ������
	sf::Color color(255, 255, 255);			//���� ��� ����
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "My Graph");	//�������� ����, � ������� ����� �������������� ����.
	window.setFramerateLimit(30);									// ����������� �� 30 fps

	thread t([&upravlenie, &gr, &dejkstra, &for_dejk, &window, &salesman, &lst, & close]()	//������������ ����� ��� ���������� ������
	{
		auto vector_my = gr.getVertexData();
		string menu;
		string data, data2;
		int menu_control;
		int weight;
		vector<string>::iterator it;
		menu = "---------------MENU--------------\n1. �������� �������\n2. ������� �������\n3. �������� �������������� �����\n4. �������� ������������ �����\n5. ������� �����\n6. �������� ��������\n7. ������ �����������\n8. ����� � ������\n9. ����� � �������\n";
		/*"---------------MENU--------------\n
		1. �������� �������\n
		2. ������� �������\n
		3. �������� �������������� �����\n
		4. �������� ������������ �����\n
		5. ������� �����\n
		6. �������� ��������\n
		7. ������ �����������\n"
		8. ����� � ������
		9. ����� � �������
		0. �����.*/

		while (true) 
		{
			cout << menu << endl << "> ";
			cin >> menu_control;
			if (!window.isOpen())
				return;
			switch (menu_control)
			{
			case 1:
				cout << "������� ������ ��� �������: " << endl << "> "; cin >> data;
				gr.addVertex(data);
				upravlenie = true;
				break;
			case 2:
				cout << "������� ������ ������� ��� ��������: " << endl << "> "; cin >> data;
				gr.removeVertex(data);
				upravlenie = true;
				break;
			case 3:
				cout << "������� 2 �������, ������� ���������� ���������: " << endl << "> "; cin >> data;
				cout << "> "; cin >> data2;
				cout << "������� ��� �����: " << endl << "> "; cin >> weight;
				gr.addEdge(data, data2, weight);
				upravlenie = true;
				break;
			case 4:
				cout << "������� 2 �������, ������� ���������� ��������� (start -> finish): " << endl << "> "; cin >> data;
				cout << "> "; cin >> data2;
				cout << "������� ��� �����: " << endl << "> "; cin >> weight;
				gr.addDirectEdge(data, data2, weight);
				upravlenie = true;
				break;
			case 5:
				cout << "������� 2 �������, ����� ����� �������� ���������� �������: " << endl << "> "; cin >> data;
				cout << "> "; cin >> data2;
				gr.removeEdge(data, data2);
				upravlenie = true;
				break;
			case 6:
				vector_my = gr.getVertexData();
				cout << "������� ��������� �������: " << endl << "> "; cin >> data;
				it = find(vector_my.begin(), vector_my.end(), data);
				if (it == vector_my.end())
				{
					cout << endl << endl << "������ ������� �� ����������." << endl;
					system("pause");
				}
				else
				{
					for_dejk = gr.dijkstra(size_t(distance(vector_my.begin(), it)));
					dejkstra = true;
					system("pause");
					dejkstra = false;
				}
				break;
			case 7:
				cout << "������� ��������� �������: " << endl << "> "; cin >> data;
				vector_my = gr.getVertexData();
				it = find(vector_my.begin(), vector_my.end(), data);
				if (it == vector_my.end())
				{
					cout << endl << endl << "������ ������� �� ����������." << endl;
					system("pause");
					break;
				}
				//gr.clearPath();
				gr.SalesmanTravel(distance(vector_my.begin(), it));
				lst = gr.getPath();
				if(lst.size() != vector_my.size())
				{
					cout << endl << endl << "������� ������ ������������ ��� ������� ����� �� ����������." << endl;
					cout << "���������� �������� ����." << endl << endl;
					system("pause");
				}
				else
				{
					cout << endl << "���� �����������:" << endl;
					for (auto& i : lst)
					{
						cout << vector_my[i] << " -> ";
					}
					cout << vector_my[lst.front()] << endl;
					cout << "���� ����: " << gr.getPathWeight() << endl << endl;
					salesman = true;
					system("pause");
					salesman = false;
				}
				break;
			case 8:
				cout << "������� ��������� �������: " << endl << "> "; cin >> data;
				cout << "����� � ������:" << endl;
				if (!gr.BFSHelper(data))
				{
					system("cls");
					cout << "������ ������� �� ����������." << endl;
					system("pause");
					break;
				}
				system("pause");
				break;
			case 9:
				cout << "������� ��������� �������: " << endl << "> "; cin >> data;
				cout << "����� � �������:" << endl;
				if (!gr.DFSHelper(data))
				{
					system("cls");
					cout << "������ ������� �� ����������." << endl;
					system("pause");
					break;
				}
				system("pause");
				break;
			default:
				menu_control = 0;
				break;
			}
			system("cls");
			string fl;			
		}
		
	});

	
	//������� ���� ��������� ���� � ������. ���� ���� �������, ��� ��������������
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
			if (event.type == sf::Event::Closed || !t.joinable()) 
			{
				window.close();
				t.join();
			}
		if (upravlenie)
		{
			upravlenie = false;
			temp_size = gr.size();
			cordCalculate(v, temp_size);
			gr.calcCordEdge(v_edges, v_direction, v);
			gr.calcCordText(v_text, v, text);
			gr.calcCordWeight(v_weight, v, text_weight);
		}

		if (salesman)
		{
			vector<sf::CircleShape> v_point;	//������ ��� ������� ���������� ������
			vector<sf::CircleShape> v_path;		//������ ��� ��������� ����������� ����
			v_path.reserve(800);
			sf::CircleShape trailShape(3.0f);
			trailShape.setFillColor(sf::Color::Red);
			trailShape.setOrigin(trailShape.getLocalBounds().width / 2, trailShape.getLocalBounds().height / 2);
			
			//�������� ������� (�������)
			sf::Image image;					
			image.loadFromFile("images/car_sprite.png");
			image.createMaskFromColor(sf::Color(255, 255, 255));
			sf::Texture texture_car;
			texture_car.loadFromImage(image);
			sf::Sprite car_sprite;
			car_sprite.setTexture(texture_car);		//������������� ��������
			car_sprite.setScale(0.7f, 0.7f);		//������������� ������ �������
			car_sprite.setOrigin(car_sprite.getLocalBounds().width / 2.0f, car_sprite.getLocalBounds().height / 2.0f);

			//�������������� ���������� ��� ��������� 
			const float animationSpeed = 300.0f; // �������� ����������� ������� (�������� � �������)
			sf::Clock clock;
			float elapsedTime = 0.0f;
			int current_local, next_local;
			sf::Vector2f temp;
			auto lst_temp = gr.getPath();
			int size_temp = lst_temp.size();
			next_local = lst_temp.front();


			for (size_t i = 1; i < size_temp; ++i)
			{
				elapsedTime = 0.0f;

				//��������� ������ ����
				current_local = next_local;
				lst_temp.pop_front();
				next_local = lst_temp.front();

				//�������� �������� ��� ������ ����
				v_point.push_back(v[current_local]);
				v_point[i - 1].setOutlineColor(sf::Color::Red);
				v_point[i - 1].setOutlineThickness(6);

				//��������� �������
				temp = v[current_local].getPosition() - v[next_local].getPosition();
				car_sprite.setPosition(v[current_local].getPosition());
				car_sprite.setRotation((atan2(temp.y, temp.x) * 180 / 3.14159) - 90);

				sf::Vector2f startPosition = v[current_local].getPosition();
				sf::Vector2f targetPosition = v[next_local].getPosition();
				sf::Vector2f distance = targetPosition - startPosition;
				float totalDistance = std::sqrt(distance.x * distance.x + distance.y * distance.y);
				float travelTime = totalDistance / animationSpeed;
				
				if (!salesman) break;
				//��������� ������� � ������
				while (elapsedTime < travelTime) 
				{
					clock.restart();
					window.clear(color);
					if (!salesman) break;
					for (int j = 0; j < v_point.size(); j++)
					{
						window.draw(v_point[j]);
					}
					for (int j = 0; j < v_edges.size(); j++)
					{
						window.draw(v_edges[j]);
						window.draw(v_direction[j]);
					}
					for (int j = 0; j < v_path.size(); j++)
					{
						window.draw(v_path[j]);
					}
					for (int j = 0; j < v.size(); j++)
					{
						window.draw(v[j]);
						window.draw(v_text[j]);
					}
					for (int j = 0; j < v_weight.size(); j++)
					{
						window.draw(v_weight[j]);
					}

					window.draw(car_sprite);
					window.display();

					elapsedTime += clock.getElapsedTime().asSeconds();

					float t = elapsedTime / travelTime;
					sf::Vector2f currentPosition = startPosition + distance * t;
					trailShape.setPosition(car_sprite.getPosition());
					v_path.push_back(trailShape);
					car_sprite.setPosition(currentPosition);
					travelTime = totalDistance / animationSpeed;
					sf::sleep(sf::milliseconds(10));
				}
			}

			v_point.push_back(v[next_local]);
			v_point.back().setOutlineColor(sf::Color::Red);
			v_point.back().setOutlineThickness(6);


			if (salesman)
			{
				elapsedTime = 0.0f;
				lst_temp = gr.getPath();
				temp = v[lst_temp.back()].getPosition() - v[lst_temp.front()].getPosition();
				car_sprite.setPosition(v[lst_temp.back()].getPosition());
				car_sprite.setRotation((atan2(temp.y, temp.x) * 180 / 3.14159) - 90);

				sf::Vector2f startPosition = v[lst_temp.back()].getPosition();
				sf::Vector2f targetPosition = v[lst_temp.front()].getPosition();
				sf::Vector2f distance = targetPosition - startPosition;
				float totalDistance = std::sqrt(distance.x * distance.x + distance.y * distance.y);
				float travelTime = totalDistance / animationSpeed;

				if (!salesman) break;

				while (elapsedTime < travelTime)
				{
					clock.restart();
					window.clear(color);
					if (!salesman) break;
					for (int j = 0; j < v_point.size(); j++)
					{
						window.draw(v_point[j]);
					}
					for (int j = 0; j < v_edges.size(); j++)
					{
						window.draw(v_edges[j]);
						window.draw(v_direction[j]);
					}
					for (int j = 0; j < v_path.size(); j++)
					{
						window.draw(v_path[j]);
					}
					for (int j = 0; j < v.size(); j++)
					{
						window.draw(v[j]);
						window.draw(v_text[j]);
					}
					for (int j = 0; j < v_weight.size(); j++)
					{
						window.draw(v_weight[j]);
					}

					window.draw(car_sprite);
					window.display();

					elapsedTime += clock.getElapsedTime().asSeconds();

					float t = elapsedTime / travelTime;
					sf::Vector2f currentPosition = startPosition + distance * t;
					trailShape.setPosition(car_sprite.getPosition());
					v_path.push_back(trailShape);
					car_sprite.setPosition(currentPosition);
					travelTime = totalDistance / animationSpeed;
					sf::sleep(sf::milliseconds(10));
				}
				while (salesman)
				{
					sf::sleep(sf::milliseconds(33)); // �������� �� ~30 ������ � �������
				}
			}
		}
		else
		{
			
			if (dejkstra)
			{
				gr.calcCordDijkstra(v_dejkstra, v, for_dejk, text);
			}
			window.clear(color);

			for (int i = 0; i < v_edges.size(); i++)
			{
				window.draw(v_edges[i]);
				window.draw(v_direction[i]);
			}

			for (int i = 0; i < v.size(); i++)
			{
				window.draw(v[i]);
			}
			for (int i = 0; i < v_text.size(); i++)
			{
				window.draw(v_text[i]);
			}
			for (int i = 0; i < v_weight.size(); i++)
			{
				window.draw(v_weight[i]);
			}

			if (dejkstra)
			{
				for (int i = 0; i < v_dejkstra.size(); i++)
					window.draw(v_dejkstra[i]);
			}
		}
		

		window.display();
			sf::sleep(sf::milliseconds(33)); // �������� �� ~30 ������ � �������
	}

	

	return 0;
}
 

//������� ������������� ����������� ������
void cordCalculate(vector <sf::CircleShape>& vec, size_t new_size)
{
	if (new_size == 0)
	{
		vec.clear();
		return;
	}
	float width, height;
	vec.clear();
	sf::CircleShape circle(40);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(sf::Color::Black);
	float radius = 400.f;					//������ �����
	sf::Vector2f center = { 500.f, 500.f };	//����� ��� ����� ��������� ����� �����
	float currentAngle = 0.f;				//������� ���������� �������� 
	float angleStep = 360.f / new_size;		//��� �������� ������������ �����
	for (int i = 0; i < new_size; i++)
	{
		circle.setPosition(center.x + radius * std::cos(currentAngle * 3.14159 / 180.f), center.y + radius * std::sin(currentAngle * 3.14159 / 180.f));
		currentAngle += angleStep;
		width = circle.getLocalBounds().width;
		height = circle.getLocalBounds().height;
		circle.setOrigin(width / 2.0f, height / 2.0f);
		vec.push_back(circle);
	}
}