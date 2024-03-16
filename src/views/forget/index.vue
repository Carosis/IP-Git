<template>
  <div class="forget">
    <h2>Reset Password</h2>
    <div class="resetEmail">
      <h3 class="label">Email Address</h3>
      <el-form
        :inline="true"
        :model="input"
        :rules="rules"
        ref="ruleForm"
        label-width="100px"
        class="demo-ruleForm"
      >
        <el-form-item prop="email">
          <el-input
            type="text"
            v-model="input.email"
            placeholder="example@email.com"
          ></el-input>
        </el-form-item>
        <el-form-item class="chock">
          <el-button
            type="primary"
            class="confirm"
            @click="submitForm('ruleForm')"
            >Confirm</el-button
          >
          <p v-if="isLabel">password reset email has boon sent, please chock</p>
        </el-form-item>
      </el-form>
    </div>
    <el-button type="primary" class="back" @click="goBack">Back</el-button>
  </div>
</template>

<script>
export default {
  name: "forgetView",
  data() {
    return {
      input: {
        email: "",
      },
      rules: {
        email: [
          { required: true, message: "Email cannot be empty", trigger: "blur" },
          {
            pattern:
              /^[a-zA-Z0-9.!#$%&amp;'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
            message: "Please enter the correct email address",
            trigger: "blur",
          },
        ],
      },
      isLabel: false,
    };
  },
  methods: {
    goBack() {
      this.$router.push("/login");
    },
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          this.isLabel = true;
        }
      });
    },
  },
};
</script>
<style lang="less" scoped>
.forget {
  padding: 7vw 0;
  h2 {
    text-align: center;
  }
  .resetEmail {
    display: flex;
    justify-content: center;
    margin: 4.5vw 0;
    align-items: center;
    /deep/ .el-form-item {
      margin-bottom: 0px !important;
    }
    /deep/ .el-form-item__content {
      margin-left: 40px !important;
      margin-right: 40px !important;
    }
    /deep/ .el-input__inner {
      width: 15vw;
    }
    .confirm {
      background-color: rgb(112, 188, 242);
      color: black;
      border-radius: 15px;
      border: 0;
    }
  }
  .back {
    position: absolute;
    top: 35%;
    left: 50%;
    transform: translateX(-50%);
    padding: 0.5vw 3vw;
    border-radius: 10px;
    border: 0;
    background-color: #d0cece;
    color: black;
  }
}
.chock {
  position: relative;
  p {
    position: absolute;
    width: 500px;
    font-size: 14px;
    bottom: -36px;
    left: -77px;
  }
}
</style>
