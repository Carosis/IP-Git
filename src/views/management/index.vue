<template>
  <div class="management">
    <div class="create">
      <span>Welcome username, your last login was on xxxx.</span>
      <el-link type="primary" href="#/login">Sign Out</el-link>
    </div>
    <div class="block" @click="update">
      <el-avatar :size="50" :src="circleUrl"></el-avatar>
    </div>
    <!-- 表格 -->
    <div class="tableOperate">
      <el-form :inline="true" :model="formInline" class="demo-form-inline">
        <el-form-item>
          <el-input
            v-model="formInline.user"
            placeholder="Username/Email"
          ></el-input>
        </el-form-item>
        <el-form-item class="search">
          <el-button type="primary">Search</el-button>
        </el-form-item>
      </el-form>
      <div class="tables">
        <el-table :data="tableData" style="width: 100%">
          <el-table-column prop="username" label="Username"></el-table-column>
          <el-table-column prop="email" label="Email"></el-table-column>
          <el-table-column prop="status" label="Status"> </el-table-column>
          <el-table-column prop="requests" label="No.of Pending Requests">
          </el-table-column>
          <el-table-column prop="lastLogin" label="Last Login">
          </el-table-column>
          <el-table-column prop="passwordExpiry" label="Password Expiry">
          </el-table-column>
          <el-table-column label="Action">
            <template slot-scope="scope">
              <el-button
                size="mini"
                @click="handleEdit(scope.$index, scope.row)"
                >More</el-button
              >
            </template>
          </el-table-column>
        </el-table>
        <div class="back">
          <el-button type="primary" @click="goBack" class="backButton"
            >Back</el-button
          >
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "managementView",
  data() {
    return {
      circleUrl:
        "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      formInline: {
        user: "",
        region: "",
      },
      tableData: [
        {
          username: "Ziling",
          email: "Zijing2002@gmail.com",
          status: "Active",
          requests: "4",
          lastLogin: "27/01/2024 15:24:37",
          passwordExpiry: "27/04/2024 09-26:33",
        },
        {
          username: "PengCheng",
          email: "Peng2017@gmail.com",
          status: "Locked",
          requests: "7",
          lastLogin: "26/01/2024 15:29:42",
          passwordExpiry: "24/04/2024 17:26:27",
        },
        {
          username: "YuLong",
          email: "Yulong02@gmail.com",
          status: "Disabled",
          requests: "0",
          lastLogin: "18/01/2024 20:29:27",
          passwordExpiry: "----------",
        },
      ],
    };
  },
  methods: {
    goBack() {
      this.$router.push("/admin");
    },
    update() {
      this.$router.push("/profile");
    },
  },
};
</script>
<style lang="less" scoped>
.management {
  padding: 1vw;
  .create,
  .block {
    display: flex;
    justify-content: end;
  }
  .block span {
    width: 70px !important;
    height: 70px !important;
  }
}
.tables {
  background-color: rgb(247, 247, 247);
}
.el-table {
  padding: 0.5vw 1vw;
  margin-top: 0.5vw;
  background-color: transparent;
  &::before {
    height: 0;
  }
}
/deep/ .el-table tr {
  cursor: pointer;
  background-color: rgb(247, 247, 247);
}
/deep/ .el-table__header-wrapper {
  border-radius: 15px;
}
/deep/.el-table thead {
  border-radius: 10px;
}
/deep/.el-table thead,
/deep/ .el-table__body {
  color: black;
}
/deep/ .el-table th.el-table__cell {
  background-color: rgb(207, 226, 255) !important;
  text-align: center;
}
/deep/ .el-table td.el-table__cell {
  text-align: center;
  border: 0 !important;
}
/deep/ .el-table td.el-table__cell .cell {
  background-color: #fff;
  padding: 0.5vw 0;
}
/deep/ .el-button {
  border-radius: 15px;
  background-color: rgb(217, 217, 217);
  color: black;
  padding: 0.2vw 1vw;
}
/deep/ .el-input__inner {
  width: 10vw !important;
  border-radius: 10px;
}
/deep/ .search .el-button {
  background-color: rgb(96, 119, 239);
  border: 0;
  padding: 0.5vw 1.5vw;
  color: #fff;
}
.back {
  display: flex;
  justify-content: center;
  padding: 2vw 0 1vw 0;

  .backButton {
    padding: 0.5vw 2vw;
    border-radius: 12px;
    border: 0;
    background-color: #d0cece;
    color: black;
    font-weight: bold;
  }
}
</style>
