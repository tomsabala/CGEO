

def getVectorType(vector):
    if not vector:
        return "null"

    types = set()
    for item in vector:
        types.add(type(item).__name__)

    if len(types) == 1:
        return types.pop()
    else:
        return "mixed"
