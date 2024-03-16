<template>
  <div class="profile">
    <h2>User Profile</h2>
    <el-form label-width="100px" class="demo-ruleForm">
      <el-form-item label="Username">
        <el-input
          type="text"
          v-model="input.user"
          :disabled="isDisabled"
        ></el-input>
      </el-form-item>
      <el-form-item label="Email">
        <el-input
          type="text"
          v-model="input.email"
          :disabled="isDisabled"
        ></el-input>
      </el-form-item>
      <el-form-item label="Password">
        <el-input
          type="password"
          v-model="input.pwd"
          :disabled="isDisabled"
          show-password
        ></el-input>
      </el-form-item>
      <el-form-item label="Confirm Password">
        <el-input
          type="password"
          v-model="input.conPwd"
          :disabled="isDisabled"
          show-password
        ></el-input>
      </el-form-item>
      <el-form-item label="Last Login">
        <el-input type="text" v-model="input.date" :disabled="true"></el-input>
      </el-form-item>
      <el-form-item>
        <template v-if="isDisabled === true">
          <el-button type="primary" @click="submitForm('ruleForm')"
            >Update</el-button
          >
          <el-button type="primary" @click="goBack">Back</el-button>
        </template>
        <template v-else>
          <el-button type="primary">Save</el-button>
          <el-button type="primary" @click="goBack">Discard</el-button>
        </template>
      </el-form-item>
    </el-form>
  </div>
</template>

<script>
export default {
  name: "profileView",
  data() {
    return {
      input: {
        user: "Ziing",
        email: "zijing2002@gmail.com",
        pwd: "new password",
        conPwd: "new password",
        date: "27/01/2024 12:08:45",
      },
      isDisabled: true,
    };
  },
  methods: {
    submitForm() {
      this.isDisabled = false;
    },
    goBack() {
      this.$router.push("/home");
    },
  },
};
</script>
<style lang="less" scoped>
.profile {
  padding: 6vw 0;
  h2 {
    text-align: center;
    padding: 0 0 1vw 0;
  }
  /deep/ .el-input {
    border: 1px solid hsla(0, 0%, 100%, 0.1);
    border-radius: 5px;
    background-color: rgba(176, 176, 176, 0.1);
    margin: 0.5vw 0;
    width: 10vw;
  }
  /deep/ form.el-form.demo-ruleForm {
    display: flex;
    justify-content: center;
    flex-direction: column;
    align-items: center;
  }
  /deep/ .el-form-item {
    display: flex;
    align-items: center;
  }
  /deep/ .el-form-item__label {
    min-width: 200px !important;
  }
  /deep/ .el-form-item__content {
    margin-left: 30px !important;
  }
  /deep/ .el-button + .el-button {
    margin-left: 80px !important;
  }
}
</style>
