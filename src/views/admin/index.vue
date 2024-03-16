<template>
  <div class="admin">
    <div class="create">
      <span>Welcome username, your last login was on xxxx.</span>
      <el-link type="primary" href="#/login">Sign Out</el-link>
    </div>
    <div class="block" @click="update">
      <el-avatar :size="50" :src="circleUrl"></el-avatar>
    </div>
    <!-- 表格 -->
    <div class="tableOperate">
      <div class="btn">
        <el-button class="request">New Request</el-button>
        <el-button class="Manage" @click="manage">Manage Users</el-button>
      </div>

      <el-table :data="tableData" style="width: 100%">
        <el-table-column prop="urls" label="url"></el-table-column>
        <el-table-column
          prop="dates"
          label="Date of Submission"
        ></el-table-column>
        <el-table-column prop="status" label="Status"></el-table-column>
        <el-table-column prop="requested" label="Requested By">
        </el-table-column>
        <el-table-column label="Action">
          <template slot-scope="scope">
            <el-button size="mini" @click="handleEdit(scope.$index, scope.row)"
              >Reject</el-button
            >
            <el-button
              size="mini"
              @click="handleDelete(scope.$index, scope.row)"
              >Approve</el-button
            >
          </template>
        </el-table-column>
      </el-table>
    </div>
  </div>
</template>

<script>
export default {
  name: "adminView",
  data() {
    return {
      circleUrl:
        "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      tableData: [
        {
          urls: "xxх.ххх.xxx.xxx",
          dates: "13/01/2024 15:20:06",
          status: "Pending",
          requested: "User1",
        },
        {
          urls: "xxх.ххх.xxx.xxx",
          dates: "19/01/2024 07:14:57",
          status: "Approved",
          requested: "User2",
        },
        {
          urls: "xxх.ххх.xxx.XxxxX",
          dates: "26/01/2024 20:14:34",
          status: "Rejected",
          requested: "User3",
        },
      ],
    };
  },
  methods: {
    manage() {
      this.$router.push("/management");
    },
    update() {
      this.$router.push("/profile");
    },
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
.admin {
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
  .btn {
    display: flex;
    justify-content: space-between;
    margin-top: 0.3vw;
    .request {
      background-color: rgb(188, 205, 239) !important;
      border-radius: 10px;
      color: black;
      padding: 0.5vw 1vw;
    }
    .Manage {
      background-color: rgb(236, 182, 78);
      color: black;
    }
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
