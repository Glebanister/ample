namespace ample::geometry
{
template <typename T = float>
std::vector<graphics::Vector2d<T>> VectorRectangle(const graphics::Vector2d<T> &size,
                                                   const graphics::Vector2d<T> &origin) // TODO: implement origin
{
    utils::ignore(origin);
    return {{-size.x / 2.0f, -size.y / 2.0f}, {-size.x / 2.0f, size.y / 2.0f}, {size.x / 2.0f, size.y / 2.0f}, {size.x / 2.0f, -size.y / 2.0f}};
}
} // namespace ample::geometry
