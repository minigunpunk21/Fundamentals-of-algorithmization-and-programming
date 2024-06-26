#include "stageonefactory.h"

#include "stageoneball.h"
#include "stageonetable.h"

#include <QColor>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

/**
 * @brief converts a value that is an object of the form {"x":float,"y":float} into a QVector2D with the appropriate values
 * @param v is the QJsonValue to convert
 * @return the QVector2D that is encoded in the JSon
 */
QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX = 0, float defaultY = 0)
{
    return QVector2D(v.toObject()["x"].toDouble(defaultX),v.toObject()["y"].toDouble(defaultY));
}

std::shared_ptr<Ball> StageOneFactory::makeBall(const QJsonObject &config) const
{
    //we kind of use a builder style setx, sety, etc, here but just because
    //it is easier than setting all the stuff in the constructor
    //this means we don't need any of the common stuff cluttering the stageOneBall class
	std::shared_ptr<StageOneBall> ball = std::make_shared<StageOneBall>();

    ball->setVelocity(QJsonValueToVector2D(config["velocity"]));
    ball->setRadius(config["radius"].toDouble(10));
    ball->setPosition(QJsonValueToVector2D(config["position"],ball->radius(),ball->radius()));
    ball->setMass(config["mass"].toDouble(1.0));
	ball->setColour(config["colour"].toString("#ffffff"));

    return ball;
}

std::shared_ptr<Table> StageOneFactory::makeTable(const QJsonObject &config) const
{
    //not really worth doing the builder style with only 3 variables
	QVector2D dimensions = QJsonValueToVector2D(config["size"],600,300);
	float friction = config["friction"].toDouble(0.01);
	QColor colour(config["colour"].toString("green"));

	return std::make_shared<StageOneTable>(dimensions.x(), dimensions.y(), friction,colour);
}
