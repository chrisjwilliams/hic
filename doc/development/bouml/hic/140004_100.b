class TestProcedureItem
!!!189540.cpp!!!	TestProcedureItem(in p : Platform = LocalHost())
    _impl.reset( new TestProcedureItemImpl( p ) );
