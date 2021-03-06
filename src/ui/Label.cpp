// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Label.h"
#include "Context.h"
#include "text/TextureFont.h"

namespace UI {

Point Label::PreferredSize()
{
	vector2f textSize;
	GetContext()->GetFont(GetFont())->MeasureString(m_text.c_str(), textSize.x, textSize.y);
	m_preferredSize = Point(ceilf(textSize.x), ceilf(textSize.y));
	return m_preferredSize;
}

void Label::Layout()
{
	if (m_preferredSize == Point())
		PreferredSize();

	const Point &size = GetSize();
	SetActiveArea(Point(std::min(m_preferredSize.x,size.x), std::min(m_preferredSize.y,size.y)));
}

void Label::Draw()
{
	static const Color disabledColor(0.8f, 0.8f, 0.8f, 1.0f);
	GetContext()->GetFont(GetFont())->RenderString(m_text.c_str(), 0.0f, 0.0f, IsDisabled() ? disabledColor : m_color);
}

Label *Label::SetText(const std::string &text)
{
	m_text = text;
	GetContext()->RequestLayout();
	return this;
}

Label *Label::SetColor(float r, float g, float b)
{
	m_color = ::Color(r, g, b);
	return this;
}

}
