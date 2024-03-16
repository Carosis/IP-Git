<template>
  <div class="login" v-cloak>
    <div class="login_view">
      <h2>Login</h2>
      <div class="login-box">
        <p>Email</p>
        <el-form
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
          <el-form-item prop="pwd">
            <div class="link">
              <p>Password</p>
              <el-link type="primary" href="#/forget" :underline="false"
                >Forgot password？</el-link
              >
            </div>
            <el-input
              type="password"
              v-model="input.pwd"
              placeholder="Password"
              show-password
            ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" @click="submitForm('ruleForm')"
              >Login</el-button
            >
          </el-form-item>
        </el-form>
        <div class="account">
          <span>Don't have account? </span>
          <el-link type="primary" href="#/register" :underline="false"
            >Create new account</el-link
          >
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "loginView",
  data() {
    return {
      input: {
        user: "",
        pwd: "",
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
        pwd: [
          {
            required: true,
            message: "Password cannot be empty",
            trigger: "blur",
          },
          {
            pattern: /^[A-Za-z0-9]+$/,
            message: "Can only contain characters, numbers, and underscores",
            trigger: "blur",
          },
        ],
      },
    };
  },
  methods: {
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          this.$router.push("/home");
        }
      });
    },
  },
};
</script>
<style lang="less" scoped>
.login {
  background-color: #eee;
  width: 100%;
  height: 100%;
  position: fixed;
  left: 0;
  top: 0;
}
.login_view {
  width: 23vw;
  height: 15vw;
  position: absolute;
  top: 30%;
  left: 50%;
  transform: translate(-50%, -30%);
  h2 {
    text-align: center;
    padding: 0 0 1vw 0;
  }
}

.login-box {
  padding: 1.2vw;
  background-color: #fff;
  border-radius: 12px;
}

/deep/ .el-input {
  border: 1px solid rgba(255, 255, 255, 0.1);
  border-radius: 5px;
  background-color: rgba(195, 190, 190, 0.1);
}
/deep/ .el-input__inner {
  background-color: transparent !important;
  border: 0;
}
/deep/ .el-form-item__content {
  position: relative;
  margin-top: 0.5vw;
  margin-left: 0 !important;
}

/deep/ .el-form-item {
  margin-bottom: 0px !important;
}

/deep/ .el-button {
  width: 100%;
  margin-top: 1vw;
  padding: 8px 20px;
  border-radius: 8px;
  font-weight: bold;
}
/deep/ .el-checkbox__label {
  color: white;
}
/deep/ .link {
  display: flex;
  justify-content: space-between;
}
.account {
  text-align: center;
  padding: 0.8vw 0 0 0;
}
</style>
