/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** AModel
*/

#include "AModel.hpp"

// Constructeur qui initialise le modèle avec une position et une rotation par défaut.
AModel::AModel(Model model) : _model(model), _islandPositionX(0.0f), _islandPositionZ(0.0f), _yRotation(0.0f) {}

// Retourne le modèle 3D associé.
Model AModel::getModel() const
{
    return _model;
}

// Définit la position sur l'île en fonction d'un index de position.
void AModel::setIslandPosition(int islandPosition = 0)
{
    float distance = 4.0f;  // distance from the center
    float angle = islandPosition * (M_PI / 3);  // angle in radians

    // Calcul des positions X et Z en utilisant les équations paramétriques d'un cercle
    _islandPositionX = distance * sin(angle);
    _islandPositionZ = distance * cos(angle);
}

// Retourne la position X calculée sur l'île.
int AModel::getIslandPositionX() const
{
    return _islandPositionX;
}

// Retourne la position Z calculée sur l'île.
int AModel::getIslandPositionZ() const
{
    return _islandPositionZ;
}

// Définit l'angle de rotation autour de l'axe Y.
void AModel::setRotationY(float yRotation)
{
    _yRotation = yRotation;
}

// Dessine le modèle à la position et à l'échelle spécifiées, avec une couleur.
void AModel::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};  // Axe de rotation
    Vector3 scaleVector = {scale, scale, scale};  // Vecteur d'échelle

    // Dessine le modèle avec les paramètres spécifiés
    DrawModelEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}

// Dessine les arêtes du modèle à la position et à l'échelle spécifiées, avec une couleur.
void AModel::drawWires(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};  // Axe de rotation
    Vector3 scaleVector = {scale, scale, scale};  // Vecteur d'échelle

    // Dessine les arêtes du modèle avec les paramètres spécifiés
    DrawModelWiresEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}
