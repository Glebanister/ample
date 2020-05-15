#pragma once

namespace ample::game::stateMachine::actions
{
template <typename T>
ObjectGroupAction<T>::ObjectGroupAction(const std::string &name,
                                        const std::string &className,
                                        const std::vector<std::string> &bodyNames)
    : Action(name, className),
      _bodyNames(std::move(bodyNames))
{
}

template <typename T>
ObjectGroupAction<T>::ObjectGroupAction(const filing::JsonIO &input)
    : Action(input),
      _bodyNames(input.read<std::vector<std::string>>("body_names"))
{
}

template <typename T>
void ObjectGroupAction<T>::updateObjectPointers()
{
    _bodyPointers.resize(_bodyNames.size());
    for (size_t i = 0; i < _bodyNames.size(); ++i)
    {
        _bodyPointers[i] = getObjectPointer(_bodyNames[i]);
    }
}

template <typename T>
std::vector<std::shared_ptr<T>> &ObjectGroupAction<T>::bodyPointers() noexcept
{
    return _bodyPointers;
}

template <typename T>
std::vector<std::string> &ObjectGroupAction<T>::bodyNames() noexcept
{
    return _bodyNames;
}

template <typename T>
void ObjectGroupAction<T>::addObjectName(const std::string &name) noexcept
{
    _bodyNames.push_back(name);
}

template <typename T>
void ObjectGroupAction<T>::onActive() // TODO: move away from onActive!
{
    updateObjectPointers();
    _pointersInitialized = true;
}

template <typename T>
std::string ObjectGroupAction<T>::dump()
{
    filing::JsonIO result = Action::dump();
    result.write<std::vector<std::string>>("body_names", _bodyNames);
    return result;
}

template <typename T>
std::shared_ptr<T> ObjectGroupAction<T>::getObjectPointer(const std::string &name)
{
    std::shared_ptr<T> result;
    try
    {
        result = std::dynamic_pointer_cast<T>(getNamespace().getObject(name));
    }
    catch (const std::bad_cast &e)
    {
        throw GameException("object with name " + name + " can not be used in " + className());
    }
    if (!result)
    {
        throw GameException("can not handle action: namespace does not contain object: " + name);
    }
    return result;
}
} // namespace ample::game::stateMachine::actions
