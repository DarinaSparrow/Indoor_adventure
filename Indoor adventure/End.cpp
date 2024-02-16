#include "End.h"

End::End()
{
	dark.setSize(Vector2f(win_width, win_height));
	dark.setFillColor(Color(0, 0, 0, 164));

	end_text.setFont(AssetManager::get_font("Resourses/weekend.ttf"));
	end_text.setCharacterSize(win_height / 10);
	end_text.setFillColor(Color::White);

	result_text.setFont(AssetManager::get_font("Resourses/weekend.ttf"));
	result_text.setCharacterSize(win_height / 12);
	result_text.setFillColor(Color::White);

	continue_text.setFont(AssetManager::get_font("Resourses/weekend.ttf"));
	continue_text.setCharacterSize(win_height / 14);
	continue_text.setFillColor(Color::White);

	end_text.setString("Unfortunately, you lost!");
	end_text.setPosition(win_width / 2 - end_text.getGlobalBounds().width / 2, win_height / 2 - end_text.getGlobalBounds().height * 2);

	ostringstream result_string;
	result_string << 0;
	result_text.setString(L"Bonuses you gained: " + result_string.str());
	result_text.setPosition(win_width / 2 - result_text.getGlobalBounds().width / 2, end_text.getGlobalBounds().top + end_text.getGlobalBounds().height);

	continue_text.setString("Press Enter to restart");
	continue_text.setPosition(win_width / 2 - continue_text.getGlobalBounds().width / 2, result_text.getGlobalBounds().top + result_text.getGlobalBounds().height);
}

void End::result(bool victory, int bonuses)
{
	if (victory)
		end_text.setString("Congratulations, you win!");
	else
		end_text.setString("Unfortunately, you lost!");
	end_text.setPosition(win_width / 2 - end_text.getGlobalBounds().width / 2, win_height / 2 - end_text.getGlobalBounds().height * 2);

	ostringstream result_string;
	result_string << bonuses;
	result_text.setString(L"Bonuses you gained: " + result_string.str());
	result_text.setPosition(win_width / 2 - result_text.getGlobalBounds().width / 2, end_text.getGlobalBounds().top + end_text.getGlobalBounds().height);
}

void End::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(dark);
	target.draw(end_text);
	target.draw(result_text);
	target.draw(continue_text);
}