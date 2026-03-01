#include <iostream>
#include <vector>

#include "GameConfig.h"
#include "Pool.h"
#include "Bullet.h"

int main()
{
	Pool<Bullet, BULLETS_POOL_SIZE> bulletPools;

	std::vector<Bullet*> currentBullets;

	for (int i = 0; i < BULLETS_POOL_SIZE/2; ++i)
	{
		auto bullet = bulletPools.Get();
		bullet->SetPosition(SCREEN_WITH / 2, SCREEN_HEIGHT / 2);
		bullet->SetTeam(i % 2);
		if (i % 2 == 0)
		{
			bullet->SetVelocity(-10);
		}
		else
		{
			bullet->SetVelocity(10);
		}

		currentBullets.push_back(bullet);
	}

	while (!currentBullets.empty())
	{
		std::vector<Bullet*> toRemove;
		for (int i = 0; i < currentBullets.size(); ++i)
		{
			currentBullets[i]->Update(0.16f);
			if (currentBullets[i]->GetPosition().second <= 0)
			{
				toRemove.push_back(currentBullets[i]);
			}

			if (currentBullets[i]->GetPosition().second >= SCREEN_HEIGHT)
			{
				toRemove.push_back(currentBullets[i]);
			}
		}
		
		for (auto&& bullet : toRemove)
		{
			auto it = std::find(currentBullets.begin(), currentBullets.end(), bullet);
			if (it != currentBullets.end())
			{
				currentBullets.erase(it);
				bulletPools.Release(bullet);
				std::cout << "returning bullet\n";
			}
			else
			{
				throw std::runtime_error("Trying to remove a non existing bullet");
			}
		}
	}

	return 0;
}