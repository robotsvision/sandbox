
function Add(a, b)
    return a + b
end

function BetterAdd(a, b)
    if type(a) ~= "number" or type(b) ~= "number" then
        error("Нефиг не числа ставить!")
    end
    return a + b
end

function BetterAdd2(a, b)
    assert(type(a) == "number", "первое число не число")
    assert(type(b) == "number", "первое число не число")
    return a + b
end

FamilyMemberTemplate = {
    name = "",
    age = 0,
    role = ""
}

function CreateMember(name, age, role)
    local member = {}
    for k, v in pairs(FamilyMemberTemplate) do
        member[k] = v
    end
    member.name = name
    member.age = age
    member.role = role
    return member
end

Family = {
    second_name = "Рыбалкины",
    mother = CreateMember("1", 0, 0),
}



