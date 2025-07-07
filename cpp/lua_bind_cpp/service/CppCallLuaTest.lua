print("run cpp call lua test")

function OnInit(id, msg)
    print("[lua] main OnInit id:" .. id .. ', msg:"' .. msg .. '"')
end

function OnExit()
    print("[lua] main OnExit")
end

TestTable = {}
TestTable.OnCall = function()
    print("[lua] Stand by")
end
