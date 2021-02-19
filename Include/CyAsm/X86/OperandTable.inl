// adc
std::initializer_list<std::initializer_list<OperandFlags::Flags>>
{
	{ OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Reg8 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::AnyGpr16To64 },
	{ OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8 },
	{ OperandFlags::AnyGpr16To64, OperandFlags::AnyGprOrMem16To64 },
	{ OperandFlags::Reg8Al, OperandFlags::Imm8 },
	{ OperandFlags::ImplicitAkkuGpr16To64, OperandFlags::Imm16 | OperandFlags::Imm32 },
	{ OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm16 | OperandFlags::Imm32 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm8 },
},
// add
std::initializer_list<std::initializer_list<OperandFlags::Flags>>
{
	{ OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Reg8 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::AnyGpr16To64 },
	{ OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8 },
	{ OperandFlags::AnyGpr16To64, OperandFlags::AnyGprOrMem16To64 },
	{ OperandFlags::Reg8Al, OperandFlags::Imm8 },
	{ OperandFlags::ImplicitAkkuGpr16To64, OperandFlags::Imm16 | OperandFlags::Imm32 },
	{ OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm16 | OperandFlags::Imm32 },
	{ OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm8 },
}
