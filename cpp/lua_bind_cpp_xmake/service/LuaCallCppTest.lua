print("run lua call cpp test")

function CallCpp()
    print("[lua] call cpp")
    local id = cppTest.CallCpp("hello cpp");
    print("[lua] id:" .. id)
end