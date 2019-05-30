# ECS-DESIGN

Simple Entity-Element-System design document.

## Component

Component design document.

### ComponentAttribute

All Components need to use `ComponentAttribute` to set the base type of them.

```C#
[Component(typeof(BaseComponent))]
class MyComponent : Component {...} 
```

### ComponentType

All Components have a property of `ComponentType`.

`ComponentType` is a class. It is used to record the type of component and id of component. 

- `Type` : Type of component.
- `Identity` : An **unique** number for different type.

### ComponentInfo

`ComponentInfo` is static class used to manager all components. 

- `TypeOf(Type)` : return component type of component.
- `InitializeComponents()` : initialize the components in this assembly.

## Entity

An index of data(like components).

There are two properties of entity. 
- `Identity` : An index of array in the pool.
- `Pool` : A reference of pool which contains this entity.

## Pool

Pool is a memory pool of entities. Entity is created or destoryed by pool.

**Before we create a pool, we need to set which component we will use in entities created by this pool.**

Pool can add components to entity and remove components from entity. And we can get a group of entities with a `match rule`.

