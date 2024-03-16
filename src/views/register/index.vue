<template>
  <div class="register">
    <div class="register_view">
      <h2>Registration Form</h2>
      <div class="register-box">
        <el-form
          :model="ruleForm"
          status-icon
          :rules="rules"
          ref="ruleForm"
          label-width="100px"
          class="demo-ruleForm"
        >
          <el-form-item prop="user">
            <el-input
              type="text"
              v-model="ruleForm.user"
              placeholder="Username"
            ></el-input>
          </el-form-item>
          <el-form-item prop="email">
            <el-input
              type="text"
              v-model="ruleForm.email"
              placeholder="email@email.com"
            ></el-input>
          </el-form-item>
          <el-form-item prop="pwd">
            <el-input
              type="password"
              v-model="ruleForm.pwd"
              placeholder="Password"
              show-password
              autocomplete="off"
            ></el-input>
          </el-form-item>
          <el-form-item prop="conPwd">
            <el-input
              type="password"
              v-model="ruleForm.conPwd"
              placeholder="Confirm Password"
              show-password
              autocomplete="off"
            ></el-input>
          </el-form-item>
          <el-form-item class="elButton">
            <el-button type="primary" @click="goBack">Back</el-button>
            <el-button type="primary" @click="submitForm('ruleForm')"
              >Submit</el-button
            >
          </el-form-item>
        </el-form>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "registerView",
  data() {
    var validatePass = (rule, value, callback) => {
      if (value === "") {
        callback(new Error("Please enter password"));
      } else {
        if (this.ruleForm.conPwd !== "") {
          this.$refs.ruleForm.validateField("conPwd");
        }
        callback();
      }
    };
    var validatePass2 = (rule, value, callback) => {
      if (value === "") {
        callback(new Error("Please enter your password again"));
      } else if (value !== this.ruleForm.pwd) {
        callback(new Error("The passwords entered twice are inconsistent!"));
      } else {
        callback();
      }
    };
    return {
      ruleForm: {
        user: "",
        email: "",
        pwd: "",
        conPwd: "",
      },
      rules: {
        user: [
          { required: true, message: "User cannot be empty", trigger: "blur" },
          {
            pattern: /^[A-Za-z0-9]+$/,
            message: "Can only contain numbers and English letters",
            trigger: "blur",
          },
        ],
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
          { validator: validatePass, trigger: "blur" },
          {
            required: true,
            message: "Password cannot be empty",
            trigger: "blur",
          },
          {
            pattern: /^[A-Za-z0-9]+$/,
            message: "只能包含字符、数字",
            trigger: "blur",
          },
        ],
        conPwd: [{ validator: validatePass2, trigger: "blur" }],
      },
    };
  },
  methods: {
    // 返回上一级
    goBack() {
      this.$router.back();
    },
    // 确定
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          if (this.register.pwd !== this.register.conPwd)
            return alert("Two passwords do not match!");
          this.$router.push("/home");
        }
      });
    },
  },
};
</script>
<style lang="less" scoped>
.register {
  background-color: #eee;
  width: 100%;
  height: 100%;
  position: fixed;
  left: 0;
  top: 0;
}
.register_view {
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
.register-box {
  padding: 1.2vw 3vw;
  background-color: #fff;
  border-radius: 4px;
}
/deep/ .el-input {
  border: 1px solid hsla(0, 0%, 100%, 0.1);
  border-radius: 5px;
  background-color: rgba(176, 176, 176, 0.1);
  margin: 0.5vw 0;
  width: 27vw;
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
.elButton {
  display: flex;
  justify-content: space-between;
  padding: 0 3vw;
  margin: 0.5vw 0;
  /deep/ .el-button {
    padding: 0.5vw 1.5vw;
  }
}
/deep/ .el-form-item__content button {
  margin: 0 50px;
}
</style>
