<template>
  <div class="home">
    <div class="create">
      <span>Welcome username, your last login was on xxxx.</span>
      <el-link type="primary" href="#/login">Sign Out</el-link>
    </div>
    <div class="block" @click="update">
      <el-avatar :size="50" :src="circleUrl"></el-avatar>
    </div>
    <!-- 表格 -->
    <div class="tableOperate">
      <el-button class="request" @click="request">New Request</el-button>
      <el-table :data="tableData" style="width: 100%">
        <el-table-column prop="urls" label="url"></el-table-column>
        <el-table-column prop="dates" label="Date of Submission">
        </el-table-column>
        <el-table-column prop="status" label="Status"> </el-table-column>
        <el-table-column label="Action">
          <template slot-scope="scope">
            <el-button size="mini" @click="handleEdit(scope.$index, scope.row)"
              >Update</el-button
            >
            <el-button
              size="mini"
              @click="handleDelete(scope.$index, scope.row)"
              >Cancel</el-button
            >
          </template>
        </el-table-column>
      </el-table>
    </div>
  </div>
</template>

<script>
export default {
  name: "HomeView",
  data() {
    return {
      circleUrl:
        "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      tableData: [
        {
          urls: "xxх.ххх.xxx.xxx",
          dates: "13/01/2024 15:20:06",
          status: "Pending",
        },
        {
          urls: "xxх.ххх.xxx.xxx",
          dates: "13/01/2024 15:20:06",
          status: "Approved",
        },
        {
          urls: "xxх.ххх.xxx.XxxxX",
          dates: "13/01/2024 15:20:06",
          status: "Rejected",
        },
      ],
    };
  },
  methods: {
    request() {
      this.$router.push("/admin");
    },
    update() {
      this.$router.push("/profile");
    }
  },
};
</script>
<style lang="less" scoped>
/deep/ .el-button {
  border-radius: 15px;
  background-color: rgb(218, 226, 217);
  color: black;
  padding: 0.2vw 1vw;
}
.home {
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
  .request {
    background-color: rgb(188, 205, 239) !important;
    border-radius: 10px;
    color: black;
    padding: 0.5vw 1vw;
  }
}
.el-table {
  background-color: rgb(247, 247, 247);
  padding: 0.5vw 1vw;
  margin-top: 0.5vw;
}
/deep/ .el-table tr {
  background-color: transparent !important;
  cursor: pointer;
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
</style>
