class Command
!!!174180.cpp!!!	setExpectedExitCodes(in codes : QSet<int>) : void
    _goodCodes += codes;
!!!174308.cpp!!!	setExpectedExitCode(in code : int) : void
    if( !_goodCodes.contains(code) )
        _goodCodes.insert(code);
!!!174052.cpp!!!	isExitCodeExpected(in code : int) : bool
    // default is to assume 0 for success
    if( _goodCodes.size() == 0 ) {
        return (code==0)?true:false;
    }
    // exit codes are defined so use them instead of
    // the default
    return _goodCodes.contains(code);
