def getVectorType(vector):
    """Return the type name if all items are the same type, 'null' if empty, 'mixed' otherwise."""
    if not vector:
        return "null"

    types = {type(item).__name__ for item in vector}
    return types.pop() if len(types) == 1 else "mixed"
