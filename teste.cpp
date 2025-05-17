#include <assert.h>
#include <math.h>

#define _U32_GARBAGE 0xF1E2D3C4U
#define _U16_GARBAGE 0xF1E2U
#define _U8_GARBAGE 0xF1U

#define _NTH_BYTE(num, n) (num >> (8 * n)) & 0xFF
#define _ALMOST_EQUAL(x, y) fabs(x - y) < 0.0001

void TEST_CASE_OP_INC()
{
    uint8_t program[] = {
        OP_INC, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 1123497651;");
    {
        vm.reset();
        vm.setRegister(R0, 1123497651);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1123497652);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.setRegister(R0, UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_FINC()
{
    uint8_t program[] = {
        OP_FINC, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        float val = 0.0f;
        float expected = 1.0f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: 1123497.12;");
    {
        float val = 1123497.12f;
        float expected = 1123498.12f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -5;");
    {
        float val = -5.0f;
        float expected = -4.0f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_DEC()
{
    uint8_t program[] = {
        OP_DEC, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT32_MAX);
    }

    printf("%s\n", "Test: 1123497651;");
    {
        vm.reset();
        vm.setRegister(R0, 1123497651);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1123497650);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.setRegister(R0, UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == (UINT32_MAX - 1));
    }
}

void TEST_CASE_OP_FDEC()
{
    uint8_t program[] = {
        OP_FDEC, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        float val = 0.0f;
        float expected = -1.0f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: 1123497.12;");
    {
        float val = 1123497.12f;
        float expected = 1123496.12f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -5;");
    {
        float val = -5.0f;
        float expected = -6.0f;
        vm.setRegister(R0, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_ADD()
{
    uint8_t program[] = {
        OP_ADD, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 + 0;");
    {
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1123497651 + 987513;");
    {
        vm.reset();
        vm.setRegister(R1, 1123497651);
        vm.setRegister(R2, 987513);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1124485164);
    }

    printf("%s\n", "Test: UINT32_MAX + 1;");
    {
        vm.reset();
        vm.setRegister(R1, UINT32_MAX);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_FADD()
{
    uint8_t program[] = {
        OP_FADD, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 + 0;");
    {
        float val = 0.0f;
        vm.setRegister(R1, *((uint32_t *)&val));
        vm.setRegister(R2, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), val));
    }

    printf("%s\n", "Test: 357.34 + 847.21;");
    {
        float val1 = 357.34f;
        float val2 = 847.21f;
        float expected = 1204.55f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -3 + -5;");
    {
        float val1 = -3.0f;
        float val2 = -5.0f;
        float expected = -8.0f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_SUB()
{
    uint8_t program[] = {
        OP_SUB, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 - 0;");
    {
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1123497651 - 987513;");
    {
        vm.reset();
        vm.setRegister(R1, 1123497651);
        vm.setRegister(R2, 987513);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1122510138);
    }

    printf("%s\n", "Test: 0 - 1;");
    {
        vm.reset();
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT32_MAX);
    }
}

void TEST_CASE_OP_FSUB()
{
    uint8_t program[] = {
        OP_FSUB, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 - 0;");
    {
        float val = 0.0f;
        vm.setRegister(R1, *((uint32_t *)&val));
        vm.setRegister(R2, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), val));
    }

    printf("%s\n", "Test: 357.34 - 847.21;");
    {
        float val1 = 357.34f;
        float val2 = 847.21f;
        float expected = -489.87f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -3 - -5;");
    {
        float val1 = -3.0f;
        float val2 = -5.0f;
        float expected = 2.0f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_MUL()
{
    uint8_t program[] = {
        OP_MUL, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 * 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 2 * 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 4);
    }

    printf("%s\n", "Test: 347 * 987513;");
    {
        vm.reset();
        vm.setRegister(R1, 347);
        vm.setRegister(R2, 987513);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 342667011);
    }
}

void TEST_CASE_OP_IMUL()
{
    uint8_t program[] = {
        OP_IMUL, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 * 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 2 * 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 4);
    }

    printf("%s\n", "Test: -3 * -5;");
    {
        int32_t val1 = -3;
        int32_t val2 = -5;
        int32_t expected = 15;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_FMUL()
{
    uint8_t program[] = {
        OP_FMUL, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 * 0;");
    {
        float val1 = 1.0f;
        float val2 = 0.0f;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&val2));
    }

    printf("%s\n", "Test: 357.34 * 847.21;");
    {
        float val1 = 357.34f;
        float val2 = 847.21f;
        float expected = 302742.0214f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -3 * -5;");
    {
        float val1 = -3.0f;
        float val2 = -5.0f;
        float expected = 15.0f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_DIV()
{
    uint8_t program[] = {
        OP_DIV, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    // printf("%s\n", "Test: 1 / 0;");
    // {
    // TODO: add code to test handling of division by zero
    // }

    printf("%s\n", "Test: 2 / 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 987513 / 347;");
    {
        vm.reset();
        vm.setRegister(R1, 987513);
        vm.setRegister(R2, 347);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 2845);
    }
}

void TEST_CASE_OP_IDIV()
{
    uint8_t program[] = {
        OP_IDIV, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    // printf("%s\n", "Test: 1 / 0;");
    // {
    // TODO: add code to test handling of division by zero
    // }

    printf("%s\n", "Test: 2 / 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: -50 / -3;");
    {
        int32_t val1 = -50;
        int32_t val2 = -3;
        int32_t expected = 16;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_FDIV()
{
    uint8_t program[] = {
        OP_FDIV, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    // printf("%s\n", "Test: 1 / 0;");
    // {
    // TODO: add code to test handling of division by zero
    // }

    printf("%s\n", "Test: 847.21 / 357.34;");
    {
        float val1 = 847.21f;
        float val2 = 357.34f;
        float expected = 2.370879275f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }

    printf("%s\n", "Test: -50 / -3;");
    {
        float val1 = -50.0f;
        float val2 = -3.0f;
        float expected = 16.666666667f;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint32_t actual = vm.getRegister(R0);
        assert(_ALMOST_EQUAL(*((float *)&actual), expected));
    }
}

void TEST_CASE_OP_SHL()
{
    uint8_t program[] = {
        OP_SHL, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 << 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 0xFF00 << 1;");
    {
        vm.reset();
        vm.setRegister(R1, 0xFF00);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0x1FE00);
    }

    printf("%s\n", "Test: 0xA310 << 16;");
    {
        vm.reset();
        vm.setRegister(R1, 0xA310);
        vm.setRegister(R2, 16);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xA3100000);
    }
}

void TEST_CASE_OP_SHR()
{
    uint8_t program[] = {
        OP_SHR, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 >> 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 0xFF00 >> 1;");
    {
        vm.reset();
        vm.setRegister(R1, 0xFF00);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0x7F80);
    }

    printf("%s\n", "Test: 0xA3100000 >> 16;");
    {
        vm.reset();
        vm.setRegister(R1, 0xA3100000);
        vm.setRegister(R2, 16);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xA310);
    }
}

void TEST_CASE_OP_ISHR()
{
    uint8_t program[] = {
        OP_ISHR, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1 >> 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: -100 >> 1;");
    {
        int32_t val1 = -100;
        int32_t expected = -50;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }

    printf("%s\n", "Test: 0xA3100000 >> 16;");
    {
        int32_t val1 = 100;
        int32_t expected = 50;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_MOD()
{
    uint8_t program[] = {
        OP_MOD, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    // printf("%s\n", "Test: 1 % 0;");
    // {
    // TODO: add code to test handling of division by zero
    // }

    printf("%s\n", "Test: 2 mod 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 987513 mod 347;");
    {
        vm.reset();
        vm.setRegister(R1, 987513);
        vm.setRegister(R2, 347);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 298);
    }
}

void TEST_CASE_OP_IMOD()
{
    uint8_t program[] = {
        OP_IMOD, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    // printf("%s\n", "Test: 1 / 0;");
    // {
    // TODO: add code to test handling of division by zero
    // }

    printf("%s\n", "Test: 2 mod 2;");
    {
        vm.reset();
        vm.setRegister(R1, 2);
        vm.setRegister(R2, 2);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: -50 mod -3;");
    {
        int32_t val1 = -50;
        int32_t val2 = -3;
        int32_t expected = -2;
        vm.reset();
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_AND()
{
    uint8_t program[] = {
        OP_AND, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 & 0;");
    {
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1 & 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1 & 1;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 0xF1F1F1F1 & 0xEAD1;");
    {
        vm.setRegister(R1, 0xF1F1F1F1);
        vm.setRegister(R2, 0xEAD1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xE0D1);
    }
}

void TEST_CASE_OP_OR()
{
    uint8_t program[] = {
        OP_OR, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 | 0;");
    {
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1 | 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 1 | 1;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 0xF1F1F1F1 | 0xEAD1;");
    {
        vm.setRegister(R1, 0xF1F1F1F1);
        vm.setRegister(R2, 0xEAD1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xF1F1FBF1);
    }
}

void TEST_CASE_OP_XOR()
{
    uint8_t program[] = {
        OP_XOR, R0, R1, R2,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 0 ^ 0;");
    {
        vm.setRegister(R1, 0);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1 ^ 0;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Test: 1 ^ 1;");
    {
        vm.setRegister(R1, 1);
        vm.setRegister(R2, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 0xF1F1F1F1 ^ 0xEAD1;");
    {
        vm.setRegister(R1, 0xF1F1F1F1);
        vm.setRegister(R2, 0xEAD1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xF1F11B20);
    }
}

void TEST_CASE_OP_NOT()
{
    uint8_t program[] = {
        OP_NOT, R0, R1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: !0;");
    {
        vm.setRegister(R1, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xFFFFFFFF);
    }

    printf("%s\n", "Test: !1;");
    {
        vm.setRegister(R1, 1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xFFFFFFFE);
    }

    printf("%s\n", "Test: !0xF1F1F1F1;");
    {
        vm.setRegister(R1, 0xF1F1F1F1);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0xE0E0E0E);
    }
}

void TEST_CASE_OP_JMP()
{
    printf("%s\n", "Teste: Jump and set 1;");
    {
        uint8_t program[] = {
            OP_JMP, 4, 0,
            OP_HALT,
            OP_LCONSB, R0, 1,
            OP_HALT};
        VM vm(program, sizeof(program));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JR()
{
    printf("%s\n", "Teste: Jump and set 1;");
    {
        uint8_t program[] = {
            OP_JR, R1,
            OP_HALT,
            OP_LCONSB, R0, 1,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R1, 3);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JZ()
{
    uint8_t program[] = {
        OP_JZ, R1, 5, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True;");
    {
        assert(vm.getRegister(R1) == 0);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False;");
    {
        vm.reset();
        vm.setRegister(R1, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JNZ()
{
    uint8_t program[] = {
        OP_JNZ, R1, 5, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True;");
    {
        vm.setRegister(R1, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False;");
    {
        vm.reset();
        assert(vm.getRegister(R1) == 0);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JE()
{
    uint8_t program[] = {
        OP_JE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False;");
    {
        vm.reset();
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R1) == 0);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JNE()
{
    uint8_t program[] = {
        OP_JNE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: False;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: True;");
    {
        vm.reset();
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R1) == 0);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JA()
{
    uint8_t program[] = {
        OP_JA, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 122);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False - equal;");
    {
        vm.reset();
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - below;");
    {
        vm.reset();
        vm.setRegister(R1, 122);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JG()
{
    uint8_t program[] = {
        OP_JG, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True - negative;");
    {
        int32_t val1 = -122;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - neg/pos;");
    {
        vm.reset();
        int32_t val1 = 1;
        int32_t val2 = -122;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False - equal;");
    {
        vm.reset();
        int32_t val1 = -123;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - below negative;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - below neg/pos;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = 1;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JAE()
{
    uint8_t program[] = {
        OP_JAE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True - above;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 122);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - equal;");
    {
        vm.reset();
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False - below;");
    {
        vm.reset();
        vm.setRegister(R1, 122);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JGE()
{
    uint8_t program[] = {
        OP_JGE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: True - greater negative;");
    {
        int32_t val1 = -122;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - greater neg/pos;");
    {
        vm.reset();
        int32_t val1 = 1;
        int32_t val2 = -122;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - equal;");
    {
        vm.reset();
        int32_t val1 = -123;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: False - below negative;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - below neg/pos;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = 1;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }
}

void TEST_CASE_OP_JB()
{
    uint8_t program[] = {
        OP_JB, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: False - above;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 122);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - equal;");
    {
        vm.reset();
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: True - below;");
    {
        vm.reset();
        vm.setRegister(R1, 122);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JL()
{
    uint8_t program[] = {
        OP_JL, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: False - greater negative;");
    {
        int32_t val1 = -122;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - greater neg/pos;");
    {
        vm.reset();
        int32_t val1 = 1;
        int32_t val2 = -122;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - equal;");
    {
        vm.reset();
        int32_t val1 = -123;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: True - below negative;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - below neg/pos;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = 1;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JBE()
{
    uint8_t program[] = {
        OP_JBE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: False - above;");
    {
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 122);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: True - equal;");
    {
        vm.reset();
        vm.setRegister(R1, 123);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - below;");
    {
        vm.reset();
        vm.setRegister(R1, 122);
        vm.setRegister(R2, 123);
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_JLE()
{
    uint8_t program[] = {
        OP_JLE, R1, R2, 6, 0,
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Teste: False - greater negative;");
    {
        int32_t val1 = -122;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: False - greater neg/pos;");
    {
        vm.reset();
        int32_t val1 = 1;
        int32_t val2 = -122;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Teste: True - equal;");
    {
        vm.reset();
        int32_t val1 = -123;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - below negative;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = -123;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }

    printf("%s\n", "Teste: True - below neg/pos;");
    {
        vm.reset();
        int32_t val1 = -124;
        int32_t val2 = 1;
        vm.setRegister(R1, *((uint32_t *)&val1));
        vm.setRegister(R2, *((uint32_t *)&val2));
        assert(vm.getRegister(R0) == 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1);
    }
}

void TEST_CASE_OP_F2I()
{
    uint8_t program[] = {
        OP_F2I, R0, R1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1345.937;");
    {
        float val = 1345.937f;
        int32_t expected = 1345;
        vm.setRegister(R1, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);

        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }

    printf("%s\n", "Test: -781345.719;");
    {
        float val = -781345.719;
        int32_t expected = -781345;
        vm.setRegister(R1, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);
        
        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_I2F()
{
    uint8_t program[] = {
        OP_I2F, R0, R1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: 1345;");
    {
        int32_t val = 1345;
        float expected = 1345.0f;
        vm.setRegister(R1, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);

        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }

    printf("%s\n", "Test: -781345;");
    {
        int32_t val = -781345;
        float expected = -781345.0f;
        vm.setRegister(R1, *((uint32_t *)&val));
        assert(vm.run() == ExecResult::VM_FINISHED);

        assert(vm.getRegister(R0) == *((uint32_t *)&expected));
    }
}

void TEST_CASE_OP_STOR()
{
    uint8_t program[] = {
        OP_STOR, 5, 0, R0,
        OP_HALT,
        0, 0, 0, 0, 0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R0, _U32_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 4);

        assert(memory[4] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(memory[9] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 4);

        assert(memory[4] == OP_HALT);
        assert(actual == 0);
        assert(memory[9] == 0xFF);
    }
}

void TEST_CASE_OP_STOR_P()
{
    uint8_t program[] = {
        OP_STOR_P, R1, R0,
        OP_HALT,
        0, 0, 0, 0, 0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U32_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 4);

        assert(memory[3] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(memory[8] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 4);

        assert(memory[3] == OP_HALT);
        assert(actual == 0);
        assert(memory[8] == 0xFF);
    }
}

void TEST_CASE_OP_STORW()
{
    uint8_t program[] = {
        OP_STORW, 5, 0, R0,
        OP_HALT,
        0, 0, 0xFF};
    VM vm(program, sizeof(program));
    uint16_t actual = 0;

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R0, _U16_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 2);

        assert(memory[4] == OP_HALT);
        assert(actual == _U16_GARBAGE);
        assert(memory[7] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 2);

        assert(memory[4] == OP_HALT);
        assert(actual == 0);
        assert(memory[7] == 0xFF);
    }
}

void TEST_CASE_OP_STORW_P()
{
    uint8_t program[] = {
        OP_STORW_P, R1, R0,
        OP_HALT,
        0, 0, 0xFF};
    VM vm(program, sizeof(program));
    uint16_t actual = 0;

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U16_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 2);

        assert(memory[3] == OP_HALT);
        assert(actual == _U16_GARBAGE);
        assert(memory[6] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 2);

        assert(memory[3] == OP_HALT);
        assert(actual == 0);
        assert(memory[6] == 0xFF);
    }
}

void TEST_CASE_OP_STORB()
{
    uint8_t program[] = {
        OP_STORB, 5, 0, R0,
        OP_HALT,
        0, 0xFF};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R0, _U8_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[4] == OP_HALT);
        assert(memory[5] == _U8_GARBAGE);
        assert(memory[6] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[4] == OP_HALT);
        assert(memory[5] == 0);
        assert(memory[6] == 0xFF);
    }
}

void TEST_CASE_OP_STORB_P()
{
    uint8_t program[] = {
        OP_STORB_P, R1, R0,
        OP_HALT,
        0, 0xFF};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Store value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U8_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[3] == OP_HALT);
        assert(memory[4] == _U8_GARBAGE);
        assert(memory[5] == 0xFF);
    }

    printf("%s\n", "Test: Store zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[3] == OP_HALT);
        assert(memory[4] == 0);
        assert(memory[5] == 0xFF);
    }
}

void TEST_CASE_OP_LOAD()
{
    uint8_t program[] = {
        OP_LOAD, R0, 5, 0,
        OP_HALT,
        _NTH_BYTE(_U32_GARBAGE, 0), _NTH_BYTE(_U32_GARBAGE, 1),
        _NTH_BYTE(_U32_GARBAGE, 2), _NTH_BYTE(_U32_GARBAGE, 3),
        0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;

    printf("%s\n", "Test: Load value;");
    {
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 4);

        assert(memory[4] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(vm.getRegister(R0) == _U32_GARBAGE);
        assert(memory[9] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        uint8_t *memory = vm.memory();

        memset(&memory[5], 0, 4);
        vm.setRegister(R0, _U32_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        memcpy(&actual, &memory[5], 4);

        assert(memory[4] == OP_HALT);
        assert(actual == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[9] == 0xFF);
    }
}

void TEST_CASE_OP_LOAD_P()
{
    uint8_t program[] = {
        OP_LOAD_P, R0, R1,
        OP_HALT,
        _NTH_BYTE(_U32_GARBAGE, 0), _NTH_BYTE(_U32_GARBAGE, 1),
        _NTH_BYTE(_U32_GARBAGE, 2), _NTH_BYTE(_U32_GARBAGE, 3),
        0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;

    printf("%s\n", "Test: Load value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 4);

        assert(memory[3] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(vm.getRegister(R0) == _U32_GARBAGE);
        assert(memory[8] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U32_GARBAGE);
        
        uint8_t *memory = vm.memory();
        memset(&memory[4], 0, 4);

        assert(vm.run() == ExecResult::VM_FINISHED);
        memcpy(&actual, &memory[4], 4);

        assert(memory[3] == OP_HALT);
        assert(actual == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[8] == 0xFF);
    }
}

void TEST_CASE_OP_LOADW()
{
    uint8_t program[] = {
        OP_LOADW, R0, 5, 0,
        OP_HALT,
        _NTH_BYTE(_U16_GARBAGE, 0), _NTH_BYTE(_U16_GARBAGE, 1),
        0xFF};
    VM vm(program, sizeof(program));
    uint16_t actual = 0;

    printf("%s\n", "Test: Load value;");
    {
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 2);

        assert(memory[4] == OP_HALT);
        assert(actual == _U16_GARBAGE);
        assert(vm.getRegister(R0) == _U16_GARBAGE);
        assert(memory[7] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        uint8_t *memory = vm.memory();

        memset(&memory[5], 0, 2);
        vm.setRegister(R0, _U32_GARBAGE);
        assert(vm.run() == ExecResult::VM_FINISHED);
        memcpy(&actual, &memory[5], 2);

        assert(memory[4] == OP_HALT);
        assert(actual == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[7] == 0xFF);
    }
}

void TEST_CASE_OP_LOADW_P()
{
    uint8_t program[] = {
        OP_LOADW_P, R0, R1,
        OP_HALT,
        _NTH_BYTE(_U16_GARBAGE, 0), _NTH_BYTE(_U16_GARBAGE, 1),
        0xFF};
    VM vm(program, sizeof(program));
    uint16_t actual = 0;

    printf("%s\n", "Test: Load value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[4], 2);

        assert(memory[3] == OP_HALT);
        assert(actual == _U16_GARBAGE);
        assert(vm.getRegister(R0) == _U16_GARBAGE);
        assert(memory[6] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U32_GARBAGE);
        
        uint8_t *memory = vm.memory();
        memset(&memory[4], 0, 2);

        assert(vm.run() == ExecResult::VM_FINISHED);
        memcpy(&actual, &memory[4], 2);

        assert(memory[3] == OP_HALT);
        assert(actual == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[6] == 0xFF);
    }
}

void TEST_CASE_OP_LOADB()
{
    uint8_t program[] = {
        OP_LOADB, R0, 5, 0,
        OP_HALT,
        _U8_GARBAGE,
        0xFF};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Load value;");
    {
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[4] == OP_HALT);
        assert(memory[5] == _U8_GARBAGE);
        assert(vm.getRegister(R0) == _U8_GARBAGE);
        assert(memory[6] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        uint8_t *memory = vm.memory();

        vm.setRegister(R0, _U32_GARBAGE);
        memory[5] = 0;
        assert(vm.run() == ExecResult::VM_FINISHED);

        assert(memory[4] == OP_HALT);
        assert(memory[5] == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[6] == 0xFF);
    }
}

void TEST_CASE_OP_LOADB_P()
{
    uint8_t program[] = {
        OP_LOADB_P, R0, R1,
        OP_HALT,
        _U8_GARBAGE,
        0xFF};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Load value;");
    {
        vm.setRegister(R1, 4);
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();

        assert(memory[3] == OP_HALT);
        assert(memory[4] == _U8_GARBAGE);
        assert(vm.getRegister(R0) == _U8_GARBAGE);
        assert(memory[5] == 0xFF);
    }

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        vm.setRegister(R1, 4);
        vm.setRegister(R0, _U32_GARBAGE);
        
        uint8_t *memory = vm.memory();
        memory[4] = 0;

        assert(vm.run() == ExecResult::VM_FINISHED);

        assert(memory[3] == OP_HALT);
        assert(memory[4] == 0);
        assert(vm.getRegister(R0) == 0);
        assert(memory[5] == 0xFF);
    }
}

void TEST_CASE_OP_MEMCPY()
{
    uint8_t program[] = {
        OP_MEMCPY, 8, 0, 12, 0, 4, 0, // copy 4 bytes from 0xC to 0x8
        OP_HALT,
        0, 0, 0, 0,
        _NTH_BYTE(_U32_GARBAGE, 0), _NTH_BYTE(_U32_GARBAGE, 1),
        _NTH_BYTE(_U32_GARBAGE, 2), _NTH_BYTE(_U32_GARBAGE, 3),
        0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;
    uint32_t source = 0;

    printf("%s\n", "Test: Copy 4 bytes;");
    {
        assert(vm.run() == ExecResult::VM_FINISHED);
        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[8], 4);
        memcpy(&source, &memory[12], 4);

        assert(memory[7] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(source == _U32_GARBAGE);
        assert(memory[16] == 0xFF);
    }
}

void TEST_CASE_OP_MEMCPY_P()
{
    uint8_t program[] = {
        OP_MEMCPY_P, R0, R1, R2,
        OP_HALT,
        0, 0, 0, 0,
        _NTH_BYTE(_U32_GARBAGE, 0), _NTH_BYTE(_U32_GARBAGE, 1),
        _NTH_BYTE(_U32_GARBAGE, 2), _NTH_BYTE(_U32_GARBAGE, 3),
        0xFF};
    VM vm(program, sizeof(program));
    uint32_t actual = 0;
    uint32_t source = 0;

    printf("%s\n", "Test: Copy 4 bytes;");
    {
        vm.setRegister(R0, 5);
        vm.setRegister(R1, 9);
        vm.setRegister(R2, 4);
        assert(vm.run() == ExecResult::VM_FINISHED);

        uint8_t *memory = vm.memory();
        memcpy(&actual, &memory[5], 4);
        memcpy(&source, &memory[9], 4);

        assert(memory[4] == OP_HALT);
        assert(actual == _U32_GARBAGE);
        assert(source == _U32_GARBAGE);
        assert(memory[13] == 0xFF);
    }
}

void TEST_CASE_OP_LCONS()
{
    printf("%s\n", "Test: Load zero;");
    {
        uint8_t program[] = {
            OP_LCONS, R0, 0, 0, 0, 0,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: Load max;");
    {
        uint8_t program[] = {
            OP_LCONS, R0, 0xFF, 0xFF, 0xFF, 0xFF,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT32_MAX);
    }
}

void TEST_CASE_OP_LCONSW()
{
    printf("%s\n", "Test: Load zero;");
    {
        uint8_t program[] = {
            OP_LCONSW, R0, 0, 0,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: Load max;");
    {
        uint8_t program[] = {
            OP_LCONSW, R0, 0xFF, 0xFF,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT16_MAX);
    }
}

void TEST_CASE_OP_LCONSB()
{
    printf("%s\n", "Test: Load zero;");
    {
        uint8_t program[] = {
            OP_LCONSB, R0, 0,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: Load max;");
    {
        uint8_t program[] = {
            OP_LCONSB, R0, 0xFF,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT8_MAX);
    }
}

void TEST_CASE_OP_MOV()
{
    uint8_t program[] = {
        OP_MOV, R0, R1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Load zero;");
    {
        vm.reset();
        vm.setRegister(R1, 0);
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: Load 1122334455U;");
    {
        vm.reset();
        vm.setRegister(R1, 1122334455U);
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == 1122334455U);
    }

    printf("%s\n", "Test: Load max;");
    {
        vm.reset();
        vm.setRegister(R1, UINT32_MAX);
        vm.setRegister(R0, _U32_GARBAGE); // set garbage
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.getRegister(R0) == UINT32_MAX);
    }
}

void TEST_CASE_OP_PUSH()
{
    uint8_t program[] = {
        OP_PUSH, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.setRegister(R0, 0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 4);
        assert(vm.stackPop() == 0);
    }

    printf("%s\n", "Test: 1123497651;");
    {
        vm.reset();
        vm.setRegister(R0, 1123497651);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 4);
        assert(vm.stackPop() == 1123497651);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.setRegister(R0, UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 4);
        assert(vm.stackPop() == UINT32_MAX);
    }
}

void TEST_CASE_OP_POP()
{
    uint8_t program[] = {
        OP_POP, R0,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.stackPush(0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == 0);
    }

    printf("%s\n", "Test: 1123497651;");
    {
        vm.reset();
        vm.stackPush(1123497651);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == 1123497651);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.stackPush(UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == UINT32_MAX);
    }
}

void TEST_CASE_OP_POP2()
{
    uint8_t program[] = {
        OP_POP2, R0, R1,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.stackPush(0);
        vm.stackPush(0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == 0);
        assert(vm.getRegister(R1) == 0);
    }

    printf("%s\n", "Test: 1123497651 / 123;");
    {
        vm.reset();
        vm.stackPush(1123497651);
        vm.stackPush(123);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == 123);
        assert(vm.getRegister(R1) == 1123497651);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.stackPush(UINT32_MAX);
        vm.stackPush(UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 0);
        assert(vm.getRegister(R0) == UINT32_MAX);
        assert(vm.getRegister(R1) == UINT32_MAX);
    }
}

void TEST_CASE_OP_DUP()
{
    uint8_t program[] = {
        OP_DUP,
        OP_HALT};
    VM vm(program, sizeof(program));

    printf("%s\n", "Test: Zero;");
    {
        vm.stackPush(0);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 8);
        assert(vm.stackPop() == 0);
        assert(vm.stackPop() == 0);
    }

    printf("%s\n", "Test: 1123497651 ;");
    {
        vm.reset();
        vm.stackPush(1123497651);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 8);
        assert(vm.stackPop() == 1123497651);
        assert(vm.stackPop() == 1123497651);
    }

    printf("%s\n", "Test: UINT32_MAX;");
    {
        vm.reset();
        vm.stackPush(UINT32_MAX);
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(vm.stackCount() == 8);
        assert(vm.stackPop() == UINT32_MAX);
        assert(vm.stackPop() == UINT32_MAX);
    }
}

uint8_t intCode;
bool intContinue;

bool handleInterrupt(uint8_t code)
{
    intCode = code;
    return intContinue;
}

void TEST_CASE_OP_INT()
{
    printf("%s\n", "Test: Code is correct;");
    {
        uint8_t program[] = {
            OP_INT, 3,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.onInterrupt(handleInterrupt);
        intContinue = true;
        intCode = 0;

        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(intCode == 3);

        vm.reset();
        uint8_t *memory = vm.memory();
        intCode = 0;
        memory[1] = 253;

        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(intCode == 253);
    }

    printf("%s\n", "Test: Can stop exec;");
    {
        uint8_t program[] = {
            OP_INT, 3,
            OP_LCONSB, R0, 123,
            OP_HALT};
        VM vm(program, sizeof(program));
        vm.onInterrupt(handleInterrupt);
        intContinue = true;
        intCode = 0;

        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(intCode == 3);
        assert(vm.getRegister(R0) == 123);
        assert(vm.getRegister(IP) == 5);

        intContinue = false;
        intCode = 0;
        vm.reset();
        assert(vm.run() == ExecResult::VM_FINISHED);
        assert(intCode == 3);
        assert(vm.getRegister(R0) == 0);
        assert(vm.getRegister(IP) == 1);
    }

    printf("%s\n", "Test: Unhandled interrupt causes error;");
    {
        uint8_t program[] = {
            OP_INT, 3,
            OP_LCONSB, R0, 123,
            OP_HALT};
        VM vm(program, sizeof(program));
        assert(vm.run() == ExecResult::VM_ERR_UNHANDLED_INTERRUPT);
        assert(vm.getRegister(IP) == 1);
    }
}

void TEST_CASE_OP_HALT()
{
    uint8_t program[] = {
        OP_HALT,
        OP_LCONSB, R0, 1,
        OP_HALT};
    VM vm(program, sizeof(program));
    vm.setRegister(R0, 123);
    assert(vm.run() == ExecResult::VM_FINISHED);
    assert(vm.getRegister(R0) == 123);
    assert(vm.getRegister(IP) == 0);
}

void TEST_CASE_OP_NOP()
{
    uint8_t program[] = {
        OP_NOP,
        OP_HALT};
    VM vm(program, sizeof(program));
    assert(vm.run() == ExecResult::VM_FINISHED);

    printf("%s\n", "Test: Registers unchanged;");
    {
        for (uint8_t i = R0; i <= T9; i++)
            assert(vm.getRegister((Register)i) == 0);
    }

    printf("%s\n", "Test: Correct IP;");
    {
        assert(vm.getRegister(IP) == 1);
    }
}

void run_testes()
{
TEST_CASE_OP_INC();
TEST_CASE_OP_FINC();
TEST_CASE_OP_DEC();
TEST_CASE_OP_FDEC();
TEST_CASE_OP_ADD();
TEST_CASE_OP_FADD();
TEST_CASE_OP_SUB();
TEST_CASE_OP_FSUB();
TEST_CASE_OP_MUL();
TEST_CASE_OP_IMUL();
TEST_CASE_OP_FMUL();
TEST_CASE_OP_DIV();
TEST_CASE_OP_IDIV();
TEST_CASE_OP_FDIV();
TEST_CASE_OP_SHL();
TEST_CASE_OP_SHR();
TEST_CASE_OP_ISHR();
TEST_CASE_OP_MOD();
TEST_CASE_OP_IMOD();
TEST_CASE_OP_AND();
TEST_CASE_OP_OR();
TEST_CASE_OP_XOR();
TEST_CASE_OP_NOT();
TEST_CASE_OP_JMP();
TEST_CASE_OP_JR();
TEST_CASE_OP_JZ();
TEST_CASE_OP_JNZ();
TEST_CASE_OP_JE();
TEST_CASE_OP_JNE();
TEST_CASE_OP_JA();
TEST_CASE_OP_JG();
TEST_CASE_OP_JAE();
TEST_CASE_OP_JGE();
TEST_CASE_OP_JB();
TEST_CASE_OP_JL();
TEST_CASE_OP_JBE();
TEST_CASE_OP_JLE();
TEST_CASE_OP_F2I();
TEST_CASE_OP_I2F();
TEST_CASE_OP_STOR();
TEST_CASE_OP_STOR_P();
TEST_CASE_OP_STORW();
TEST_CASE_OP_STORW_P();
TEST_CASE_OP_STORB();
TEST_CASE_OP_STORB_P();
TEST_CASE_OP_LOAD();
TEST_CASE_OP_LOAD_P();
TEST_CASE_OP_LOADW();
TEST_CASE_OP_LOADW_P();
TEST_CASE_OP_LOADB();
TEST_CASE_OP_LOADB_P();
TEST_CASE_OP_MEMCPY();
TEST_CASE_OP_MEMCPY_P();
TEST_CASE_OP_LCONS();
TEST_CASE_OP_LCONSW();
TEST_CASE_OP_LCONSB();
TEST_CASE_OP_MOV();
TEST_CASE_OP_PUSH();
TEST_CASE_OP_POP();
TEST_CASE_OP_POP2();
TEST_CASE_OP_DUP();
TEST_CASE_OP_INT();
TEST_CASE_OP_HALT();
TEST_CASE_OP_NOP();
}