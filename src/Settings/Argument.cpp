/*  Copyright (C) Tim van Mourik, 2014-2016
    Copyright (C) Tim van Mourik, 2017, DCCN
    All rights reserved

 This file is part of the Porcupine pipeline tool, see
 https://github.com/TimVanMourik/Porcupine for the documentation and
 details.

    This toolbox is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the fmri analysis toolbox. If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <QJsonArray>

#include "Argument.hpp"

Argument::Argument(
        const QJsonObject& _json
        ) :
    m_isInput     (_json["input"  ].toBool()),
    m_isOutput    (_json["output" ].toBool()),
    m_isVisible   (_json["visible"].toBool()),
    m_argumentName(_json["name"   ].toString()),
    m_defaultValue(_json["value"  ].toString()),
    m_json(_json)
{
    foreach (QJsonValue code, _json["code"].toArray())
    {
        QJsonObject codeJson = code.toObject();
        addCode(codeJson["language"].toString(),
                codeJson["argument"].toString(),
                codeJson["comment" ].toString());
    }

}

void Argument::setName(
        const QString& _name
        )
{
    m_argumentName = _name;
}

bool Argument::isInput(
        ) const
{
    return m_isInput;
}

bool Argument::isOutput(
        ) const
{
    return m_isOutput;
}

bool Argument::isVisible(
        ) const
{
    return m_isVisible;
}

void Argument::setDefault(
        const QString& _default
        )
{
    m_defaultValue = _default;
}

void Argument::setVisible(
        bool _editable
        )
{
    m_isVisible = _editable;
}

const QString& Argument::getName(
        ) const
{
    return m_argumentName;
}

const QString& Argument::getDefault(
        ) const
{
    return m_defaultValue;
}

QString Argument::getArgument(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].argument;
    }
    else
    {
        return QString();
    }
}


const QJsonObject& Argument::getJson(
        ) const
{
    return m_json;
}

QString Argument::getComment(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].comment;
    }
    else
    {
        return QString();
    }
}

void Argument::addCode(
        const QString& _language,
        const QString& _function,
        const QString& _comment
        )
{
    m_code[_language] = Code();
    m_code[_language].argument = _function;
    m_code[_language].comment  = _comment;
}
